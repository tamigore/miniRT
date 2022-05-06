/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:03 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:35:42 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define LUMEN 100

/*
**	shade : Get the object lights specular + direct.
*/

t_vec	rgbzed(double intens, t_vec obj_color, t_vec lgt_color)
{
	double	x;
	double	y;
	double	z;

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

/*
**t_vec			reflect_vec(t_vec vec, t_vec axis)
**{
**	t_mat	rotmatrix;
**
**	rotmatrix = rotmat_axis_angle(axis, deg2rad(180));
**	return (v_norm(mat_mult_vec(rotmatrix, vec)));
**}
**
**t_vec	get_specular(t_ray *ray, t_lgt *light, t_vec to_light)
**{
**	t_vec		rgb;
**	t_vec		reflect;
**	t_vec		to_view;
**	float		mult_value;
**	float		dotproduct;
**
**	dotproduct = v_dot(v_norm(v_sub(ray->hit_pos, light->pos)), ray->normal);
**	if (abs(dotproduct) > 1)
**		printf("failure dot\n");
**	if (dotproduct <= 0)
**		return (rgb_init(0));
**	reflect = reflect_vec(v_norm(v_sub(ray->hit, light->pos)), ray->normal);
**	to_view = v_norm(v_sub(ray->hit_pos, cam->pos));
**	mult_value = vec_dotproduct(reflect, to_view)) > 0 ?
**		vec_dotproduct(reflect, to_view)) : 0;
**	mult_value = powf(mult_value, 2);
**	mult_value *= light->ratio;
**	rgb = rgb_mul(light->color, mult_value);
**	rgb_updatevalue(&rgb);
**	return (rgb);
**}
*/

void	lights(t_obj *obj, t_ray *ray, t_env *env, t_vec *color)
{
	t_vec	tmp_col;
	t_lgt	*tmp;
	t_ray	r;
	double	intens;

	tmp = env->lgt;
	while (tmp)
	{
		r.dir = v_norm(v_sub(tmp->pos, ray->hit));
		set_ray(&r, ray->hit, r.dir, v_len(v_sub(tmp->pos, ray->hit)));
		if (!hit_objs(env->obj, &r))
		{
			if (v_dot(r.dir, ray->normal) >= 0 && v_dot(ray->dir,
					ray->normal) <= 0)
			{
				intens = (LUMEN * tmp->ratio * v_dot(r.dir, ray->normal))
					/ (v_len(v_scale(r.t, r.dir)) * v_len(v_scale(r.t, r.dir)));
				if (intens > 1)
					intens = 1;
				tmp_col = rgbzed(intens, get_obj_color(obj), tmp->color);
				*color = rescale_vec(v_add(tmp_col, *color), 0, MAX_RGB);
			}
		}
		tmp = tmp->next;
	}
}

void	shade(t_env *env, t_ray *ray)
{
	t_obj	*hit_obj;
	t_vec	color;

	ray->dir = v_norm(ray->dir);
	hit_obj = hit_objs(env->obj, ray);
	if (hit_obj)
	{
		ray->hit = v_add(ray->pos, v_scale(ray->t, ray->dir));
		get_obj_normal(hit_obj, ray);
		color = rgbzed(env->amb.ratio, get_obj_color(hit_obj), env->amb.color);
		lights(hit_obj, ray, env, &color);
		ray->color = color;
	}
}

/*
**	put_pixel_to_image : Apply the color into an array for the given pixel
**		according to the mlx librairy.
*/

void	put_pixel_to_image(t_img img, t_vec color, int x, int y)
{
	int		i;

	i = (x * PIXEL_LEN + img.size_line * y);
	color = rescale_vec(color, 0, MAX_RGB);
	img.pixels[i + TRANS] = (unsigned int)0;
	img.pixels[i + RED] = (unsigned int)color.x;
	img.pixels[i + GREEN] = (unsigned int)color.y;
	img.pixels[i + BLUE] = (unsigned int)color.z;
}
