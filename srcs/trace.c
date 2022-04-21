/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/21 18:36:02 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	shade : Get the object lights specular + direct.
*/
t_vec	vec_scale_rgb(float x, t_vec a)
{
	t_vec	vec;

	vec.x = a.x * x;
	vec.y = a.y * x;
	vec.z = a.z * x;
	if (vec.x > 255)
		vec.x = 255;
	if (vec.y > 255)
		vec.y = 255;
	if (vec.z > 255)
		vec.z = 255;
	return (vec);
}

t_vec	vec_add_rgb(t_vec a, t_vec b)
{
	t_vec vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	if (vec.x > 255)
		vec.x = 255.0;
	if (vec.y > 255.0)
		vec.y = 255.0;
	if (vec.z > 255)
		vec.z = 255.0;
	return (vec);
}

t_vec	rgbzed(float intens, t_vec obj_color, t_vec lgt_color)
{
	float x;
	float y;
	float z;

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
	return (vec_scale(intens, (vec_init(x, y, z, 0))));
}

int		hit_objs(t_obj *obj, t_ray *ray, float *t, t_obj *closer)
{
	int ret;
	t_obj *tmp;
	int i;
	float dist;
	
	dist = 1.0 /0.0;
	i = 0;
	tmp = obj;
	ret = 0;
	while (tmp)
	{
		i++;
		ret += hit_obj(tmp, ray, t);
		if (dist > *t)
		{
			dist = *t;
			closer = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_vec	lights(t_obj *obj, t_ray *ray, t_lgt *light, t_amb amb)
{
	t_vec color;
	t_vec tmp_col;
	t_vec P;
	t_lgt *tmp;
	t_ray tmp_ray;
	float intens;
	float t;

	P = vec_add(ray->pos, vec_init(ray->dir.x * ray->t,ray->dir.y * ray->t,ray->dir.z * ray->t, 0));
	tmp = light;
	color = rgbzed(amb.ratio, get_obj_color(obj), amb.color);
	while (tmp)
	{
		intens = ((10 * tmp->ratio) * vec_dot(vec_norm(vec_sub(tmp->pos, P)), ray->normal)) / pow(vec_len(vec_sub(tmp->pos, P)),1);
		tmp_ray.pos = ray->hit;
		tmp_ray.dir = vec_norm(vec_sub(tmp->pos, ray->hit));
		reset_ray(&tmp_ray);
		if (!hit_objs(obj, &tmp_ray, &t, NULL))
		{
			tmp_col = rgbzed(intens, get_obj_color(obj), tmp->color);
			color = vec_add_rgb(tmp_col, color);
		}
		tmp = tmp->next;
	}
	return (color);
}

void			shade(t_env *env, t_ray *ray)
{
	t_obj			*hit_obj;

	hit_obj = trace_objs(env->obj, ray);
	if (hit_obj)
	{
		ray->color = get_obj_color(hit_obj);
		ray->hit = vec_add(ray->pos, vec_scale(ray->t, ray->dir));
		get_obj_normal(hit_obj, ray);
		ray->color = lights(hit_obj, ray, env->lgt, env->amb );
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
