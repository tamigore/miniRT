/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/31 15:23:36 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	shade : Get the object lights specular + direct.
*/
t_v3	v_multi_rgb(double x, t_v3 a)
{
	t_v3	vec;

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

t_v3	v_add_rgb(t_v3 a, t_v3 b)
{
	t_v3 vec;

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

int		hit_objs(t_obj *obj, t_ray *ray, double *t)
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

t_v3	lights(t_obj *obj, t_ray *ray, t_lgt *light, t_amb amb)
{
	t_v3 color;
	t_v3 tmp_col;
	t_v3 P;
	t_v3 N;
	t_lgt *tmp;
	t_ray tmp_ray;
	double intens;
	double t;

	(void)amb;
	P = v_add(ray->pos, v_init(ray->dir.x * ray->t,ray->dir.y * ray->t,ray->dir.z * ray->t));
	N = v_norm(v_sub(P, ((t_sph *)(obj->data))->pos));	
	intens = (100 * light->ratio) * v_dot(v_norm(v_sub(light->pos, P)), N) / pow(v_len(v_sub(light->pos, P)),2);
	//printf("Color before: %f | %f | %f\n", ray->color.x, ray->color.y, ray->color.z);
	tmp = light;
	color = rgbzed(amb.ratio, ((t_sph *)(obj->data))->color, amb.color);
	while (tmp)
	{
		intens = (100 * tmp->ratio) * v_dot(v_norm(v_sub(tmp->pos, P)), N) / pow(v_len(v_sub(tmp->pos, P)),2);
		//printf("itens : %f\n", intens);
		tmp_ray.pos = ray->hit;
		tmp_ray.dir = v_norm(v_sub(tmp->pos, ray->hit));
		tmp_col = rgbzed(intens, ((t_sph *)(obj->data))->color, tmp->color);
	//	printf("x %4.4f | y %4.4f | z %4.4f\n", tmp_col.x, tmp_col.y, tmp_col.z);
		if (!hit_objs(obj, &tmp_ray, &t))
		{
		//	printf("adding color : \n");
		//	printf("color : x %4.4f | y %4.4f | z %4.4f\n", color.x, color.y, color.z);
		//	printf("tmp_c : x %4.4f | y %4.4f | z %4.4f\n", tmp_col.x, tmp_col.y, tmp_col.z);
			color = v_add_rgb(tmp_col, color);
		//	printf("equal : x %4.4f | y %4.4f | z %4.4f\n", color.x, color.y, color.z);
		}
		tmp = tmp->next;
	}
	//printf("end of additions\n");
	//printf("Color after: %f | %f | %f\n", color.x, color.y, color.z);
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
		//printf("function before: %f | %f | %f\n", ray->color.x, ray->color.y, ray->color.z);
		ray->color = lights(hit_obj, ray, env->lgt, env->amb );
	}
}

/*
**	put_pixel_to_image : Apply the color into an array for the given pixel
**		according to the mlx librairy.
*/

static void			put_pixel_to_image(t_img img, t_v3 color, int x, int y)
{
	int		i;

	i = (x * PIXEL_LEN + img.size_line * y);
	color = rescale_vec(color, 0, MAX_RGB);
	img.pixels[i + TRANS] = (unsigned int)0;
	img.pixels[i + RED] = (unsigned int)color.x;
	img.pixels[i + GREEN] = (unsigned int)color.y;
	img.pixels[i + BLUE] = (unsigned int)color.z;
}

/*
**	trace_ray : Does all the raytracing.
*/

void				trace_ray(t_env *env)
{
	unsigned int	x;
	unsigned int	y;
	t_ray			ray;

	y = 0;
	printf("env->img = %p\n", &(env->cam->img));
	ray.pos = env->cam->pos;
	while (y < (unsigned int)env->res.y -1)
	{
		x = 0;
		while (x < (unsigned int)env->res.x - 1)
		{
			reset_ray(&ray);
			ray.dir = canvas2view(env, env->cam, x, y);
			shade(env, &ray);
			put_pixel_to_image(env->cam->img, ray.color, x, y);
			x++;
		}
		y++;
	}
}
