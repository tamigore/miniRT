/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2021/04/20 12:30:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		ray->hit = v_add(ray->pos, v_multi(ray->t, ray->dir));
		get_obj_normal(hit_obj, ray);
		ray->color = trace_ray_to_light(env, ray); // creat lights
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
//	cam->cam2world = lookAt(cam->cam2world, cam->dir, cam->pos);
//	if (!cam->cam2world)
//		exit_error(env, ERRNO_TO_STR);
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
