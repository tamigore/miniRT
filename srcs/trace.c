/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 19:06:45 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	shade : Get the object lights specular + direct.
*/

t_vec	rgbzed(double intens, t_vec obj_color, t_vec lgt_color)
{
	t_vec new;

	new = v_add(obj_color, v_scale(intens, lgt_color));
	return (rescale_vec(new, 0, MAX_RGB));
}

t_vec	lights(t_obj *obj, t_ray *ray, t_env *env)
{
	t_vec color;
	t_vec tmp_col;
	t_lgt *tmp;
	t_ray tmp_ray;
	double intens;

	tmp = env->lgt;
	color = rgbzed(env->amb.ratio, get_obj_color(obj), env->amb.color);
	while (tmp)
	{
		intens = (tmp->ratio * v_dot(v_norm(v_sub(tmp->pos, ray->hit)), ray->normal)) / pow(v_len(v_sub(tmp->pos, ray->hit)), 2);
		tmp_ray.t = v_len(v_sub(tmp->pos, ray->hit));
		tmp_ray.pos = ray->hit;
		tmp_ray.dir = v_norm(v_sub(tmp->pos, ray->hit));
		if (!hit_objs(env->obj, &tmp_ray))
		{
			tmp_col = rgbzed(intens, get_obj_color(obj), tmp->color);
			color = rescale_vec(v_add(tmp_col, color), 0, MAX_RGB);
		}
		tmp = tmp->next;
	}
	if (!env->obj)
		printf("error no obj !!!\n");
	return (color);
}

void			shade(t_env *env, t_ray *ray)
{
	t_obj			*hit_obj;

	ray->dir = v_norm(ray->dir);
	hit_obj = hit_objs(env->obj, ray);
	if (hit_obj)
	{
		// ray->color = get_obj_color(hit_obj);
		ray->hit = v_add(ray->pos, v_scale(ray->t, ray->dir));
		get_obj_normal(hit_obj, ray);
		ray->color = lights(hit_obj, ray, env);
	}
}

/*
**	put_pixel_to_image : Apply the color into an array for the given pixel
**		according to the mlx librairy.
*/

void			put_pixel_to_image(t_img img, t_vec color, int x, int y)
{
	int		i;

	i = (x * PIXEL_LEN + img.size_line * y);
	color = rescale_vec(color, 0, MAX_RGB);
	img.pixels[i + TRANS] = (unsigned int)0;
	img.pixels[i + RED] = (unsigned int)color.x;
	img.pixels[i + GREEN] = (unsigned int)color.y;
	img.pixels[i + BLUE] = (unsigned int)color.z;
}
