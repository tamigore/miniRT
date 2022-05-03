/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/03 20:03:25 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define LUMEN 100

/*
**	shade : Get the object lights specular + direct.
*/

t_vec    rgbzed(double intens, t_vec obj_color, t_vec lgt_color)
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
    return (v_scale(intens, (v_init(x, y, z, 0))));
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
		reset_ray(&tmp_ray);
		tmp_ray.t = v_len(v_sub(ray->hit, tmp->pos));
		tmp_ray.pos = ray->hit;
		tmp_ray.dir = v_norm(v_sub(tmp->pos, ray->hit));
		if (!hit_objs(env->obj, &tmp_ray))
		{
			if (v_dot(tmp_ray.dir, ray->normal) >= 0)
			{
				intens = fabs((LUMEN * tmp->ratio * v_dot(tmp_ray.dir, ray->normal)) / pow(v_len(v_scale(tmp_ray.t, tmp_ray.dir)), 2));
				intens = (intens > 1 ? 1 : intens);
				tmp_col = rgbzed(intens, get_obj_color(obj), tmp->color);
				color = rescale_vec(v_add(tmp_col, color), 0, MAX_RGB);
			}
		}
		tmp = tmp->next;
	}
	return (color);
}

void			shade(t_env *env, t_ray *ray)
{
	t_obj			*hit_obj;

	ray->dir = v_norm(ray->dir);
	hit_obj = hit_objs(env->obj, ray);
	if (hit_obj)
	{
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
