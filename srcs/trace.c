/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 17:12:54 by tamigore         ###   ########.fr       */
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

int		hit_objs(t_obj *obj, t_ray *ray, float *t)
{
	int ret;
	t_obj *tmp;

	tmp = obj;
	ret = 0;
	while (tmp)
	{
		ret = hit_obj(tmp, ray, t);
		tmp = tmp->next;
	}
	//printf("ret : %d\n", ret);
	return (ret);
}

t_vec	lights(t_obj *obj, t_ray *ray, t_lgt *light, t_amb amb)
{
	t_vec color;
	t_vec tmp_col;
	t_vec P;
	t_vec N;
	t_lgt *tmp;
	t_ray tmp_ray;
	float intens;
	float t;

	(void)amb;
	P = vec_add(ray->pos, vec_init(ray->dir.x * ray->t,ray->dir.y * ray->t,ray->dir.z * ray->t, 0));
	N = vec_norm(vec_sub(P, ((t_sph *)(obj->data))->pos));	
	//printf("Color before: %f | %f | %f\n", ray->color.x, ray->color.y, ray->color.z);
	tmp = light;
	color = rgbzed(amb.ratio, ((t_sph *)(obj->data))->color, amb.color);
	while (tmp)
	{
		intens = (100 * tmp->ratio) * vec_dot(vec_norm(vec_sub(tmp->pos, P)), N) / pow(vec_len(vec_sub(tmp->pos, P)),2);
		//printf("itens : %f\n", intens);
		tmp_ray.pos = ray->hit;
		tmp_ray.dir = vec_norm(vec_sub(tmp->pos, ray->hit));
		tmp_col = rgbzed(intens, ((t_sph *)(obj->data))->color, tmp->color);
	//	printf("x %4.4f | y %4.4f | z %4.4f\n", tmp_col.x, tmp_col.y, tmp_col.z);
		if (!hit_objs(obj, &tmp_ray, &t))
		{
		//	printf("adding color : \n");
		//	printf("color : x %4.4f | y %4.4f | z %4.4f\n", color.x, color.y, color.z);
		//	printf("tmp_c : x %4.4f | y %4.4f | z %4.4f\n", tmp_col.x, tmp_col.y, tmp_col.z);
			color = vec_add_rgb(tmp_col, color);
		//	printf("equal : x %4.4f | y %4.4f | z %4.4f\n", color.x, color.y, color.z);
		}
		tmp = tmp->next;
	}
	//printf("end of additions\n");
	//printf("Color after: %f | %f | %f\n", color.x, color.y, color.z);
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
		// ray->color = trace_ray_to_light(env, ray); // creat lights
		// printf("function before: %f | %f | %f\n", ray->color.x, ray->color.y, ray->color.z);
		// ray->color = lights(hit_obj, ray, env->lgt, env->amb );
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
	// if (color.x >= MAX_RGB || color.y >= MAX_RGB || color.z >= MAX_RGB)
	// 	printf("color : x = %f || y = %f || z = %f\n", color.x, color.y, color.z);
	color = rescale_vec(color, 0, MAX_RGB);
	img.pixels[i + TRANS] = (unsigned int)0;
	img.pixels[i + RED] = (unsigned int)color.x;
	img.pixels[i + GREEN] = (unsigned int)color.y;
	img.pixels[i + BLUE] = (unsigned int)color.z;
}

/*
**	trace_ray : Does all the raytracing.
*/

t_vec	get_orthogonal(t_vec vec)
{
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;

	v1 = vec_cross(vec_init(1, 0, 0, 0), vec);
	v2 = vec_cross(vec_init(0, 1, 0, 0), vec);
	v3 = vec_cross(vec_init(0, 0, 1, 0), vec);
	if (vec_dot(v1, vec) == 0)
		return (v1);
	else if (vec_dot(v2, vec) == 0)
		return (v2);
	else if (vec_dot(v3, vec) == 0)
		return (v3);
	return (vec_init(0, 0, 0, 0));
}
