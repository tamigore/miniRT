/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2021/03/17 18:01:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	vector_direct : Takes the (x, y) pixel of our screen and transform it to
**		camera space.
*/

static t_v3			vector_direct(int fov, int resX, int resY, int x, int y)
{
	double			Px;
	double			Py;
	double			ratio;
	double			tang;

	tang = tan(rad(fov) / 2);
	ratio = resX / resY;
	Px = (2 * ((x + 0.5) / resX) - 1) * ratio * tang;
	Py = (1 - 2 * ((y + 0.5) / resY)) * tang;
	return (v_init(Px, Py, 1));
}

/*
**	canvas2view : Take the canvas point (x, y) and transform it to 3d world.
*/

static t_v3			canvas2view(t_env *env, t_cam *cam, int x, int y)
{
	t_v3			vec;

	vec = vector_direct(cam->fov, env->res.x, env->res.y, x, y);
	vec = vec3_x_mat4(vec, cam->cam2world);
	vec = v_norm(vec);
	return (vec);
}

/*
**	shade : Get the object lights specular + direct.
*/

static void			shade(t_env *env, t_ray *ray)
{
	t_obj			*hit_obj;

	hit_obj = trace_objs(env->obj, ray);
	if (hit_obj)
	{
		get_obj_color(hit_obj, ray);
		v_multi(1/255, ray->color);
//		printf("basic color : %f.R / %f.G / %f.B\n", ray->color.x, ray->color.y, ray->color.z);
		ray->hit = v_add(ray->pos, v_multi(ray->t, ray->dir));
		get_obj_normal(hit_obj, ray);
		ray->color = trace_ray_to_light(env, ray);
//		printf("light color : %f.R / %f.G / %f.B\n", ray->color.x, ray->color.y, ray->color.z);

	}
}

/*
**	put_pixel_to_image : Apply the color into an array for the given pixel
**		according to the mlx librairy.
*/

static void			put_pixel_to_image(t_env *env, t_v3 color, int x, int y)
{
	int				i;

	i = (x * PIXEL_LEN + env->img->size_line * y);
	color = rescale_vec(color, 0, MAX_RGB);
	env->img->pixels[i + TRANS] = (unsigned int)0;
	env->img->pixels[i + RED] = (unsigned int)color.x;
	env->img->pixels[i + GREEN] = (unsigned int)color.y;
	env->img->pixels[i + BLUE] = (unsigned int)color.z;
}

/*
**	trace_ray : Does all the raytracing.
*/

void				trace_ray(t_env *env, t_cam *cam)
{
	unsigned int	x;
	unsigned int	y;
	t_ray			ray;

	y = 0;
	cam->cam2world = lookAt(cam->cam2world, cam->dir, cam->pos);
	if (!cam->cam2world)
		exit_error(env, ERRNO_TO_STR);
	ray.pos = env->cam->pos;
	while (y < (unsigned int)env->res.y)
	{
		x = 0;
		while (x < (unsigned int)env->res.x)
		{
			reset_ray(&ray);
			ray.dir = canvas2view(env, cam, x, y);
			shade(env, &ray);
			put_pixel_to_image(env, ray.color, x, y);
			x++;
		}
		y++;
	}
}
