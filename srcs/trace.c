/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanter <dasanter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/17 18:49:43 by dasanter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	shade : Get the object lights specular + direct.
*/

t_v3	rgbzed(double intens, t_v3 obj_color, t_v3 lgt_color)
{
	double x;
	double y;
	double z;

	if (obj_color.x < lgt_color.x)
		x = obj_color.x;
	else 
		x = lgt_color.x;
	if (obj_color.y < lgt_color.y)
		y = obj_color.y;
	else 
		y = lgt_color.y;
	if (obj_color.z < lgt_color.z)
		z = obj_color.z;
	else 
		z = lgt_color.z;
	return (v_multi(intens, (v_init(x,y,z))));
}

t_v3	lights(t_obj *obj, t_ray *ray, t_lgt *light)
{
	t_v3 color;
	t_v3 P;
	t_v3 N;
	t_lgt *tmp;
	double intens;

	P = v_add(ray->pos, v_init(ray->dir.x * ray->t,ray->dir.y * ray->t,ray->dir.z * ray->t));
	N = v_norm(v_sub(P, ((t_sph *)(obj->data))->pos));	
	intens = (100 * light->ratio) * v_dot(v_norm(v_sub(light->pos, P)), N) / pow(v_len(v_sub(light->pos, P)),2);
	printf("Color before: %f | %f | %f\n", ray->color.x, ray->color.y, ray->color.z);
	tmp = light;
	color = light->color;
	while (tmp)
	{
		printf("NEW COLOR : %f | %f | %f\n", color.x,color.y,color.z);
		if (tmp->next)
			color = v_add(color, tmp->next->color);
		tmp = tmp->next;
	}
	color = rgbzed(intens, ray->color, color);
	printf("Color after: %f | %f | %f\n", color.x, color.y, color.z);
	return (color);
}

static void			shade(t_env *env, t_ray *ray)
{
	t_obj			*hit_obj;

	hit_obj = trace_objs(env->obj, ray);
	if (hit_obj)
	{
		get_obj_color(hit_obj, ray);
		ray->hit = v_add(ray->pos, v_multi(ray->t, ray->dir));
		get_obj_normal(hit_obj, ray);
		//ray->color = trace_ray_to_light(env, ray); // creat lights
		printf("function before: %f | %f | %f\n", ray->color.x, ray->color.y, ray->color.z);
		ray->color = lights(hit_obj, ray, env->lgt);
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
	ray.pos = cam->pos;
	while (y < (unsigned int)env->res.y -1)
	{
		x = 0;
		while (x < (unsigned int)env->res.x - 1)
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
