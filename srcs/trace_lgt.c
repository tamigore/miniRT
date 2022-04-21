/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_lgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:20:47 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/21 17:32:44 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		is_in_shadow(t_env *env, t_ray *ray, t_vec lgt_dir)
{
	t_obj		*tmp;
	t_ray		shadow_ray;
	float		t;

	t = vec_len(lgt_dir);
	set_ray(&shadow_ray, ray->hit, vec_norm(lgt_dir), t);
	tmp = env->obj;
	while (tmp)
	{
		if (hit_obj(tmp, &shadow_ray, &t))
		{
			if (t < shadow_ray.t)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static float	get_specular(t_ray *ray, t_lgt *lgt, t_vec lgt_dir, float pov)
{
	t_vec	rev_dir;
	t_vec	reflect;
	float	coef;

	coef = 1;
	rev_dir = vec_scale(-1, ray->dir);
	reflect = vec_sub(vec_scale((2 * pov), ray->normal), vec_norm(lgt_dir));
	if (vec_dot(reflect, rev_dir) > 0.0)
		coef = lgt->ratio * pow(vec_cos(reflect, rev_dir), 70);
	return (coef);
}

static void		compute_lgt(t_env *env, t_lgt *lgt, t_ray *ray, t_vec *color)
{
	t_vec		lgt_dir;
	float		pov;
	float		lum;
	float		spec_lum;

	lgt_dir = vec_norm(vec_sub(lgt->pos, ray->hit));
	pov = vec_dot(ray->normal, lgt_dir);
	lum = 0;
	spec_lum = 0;
	if (!is_in_shadow(env, ray, lgt_dir) && pov > 0.0)
	{
		lum = lgt->ratio * vec_cos(ray->normal, lgt_dir);
		*color = vec_scale(lum, lgt->color);
		spec_lum = get_specular(ray, lgt, lgt_dir, pov);
		*color = vec_add(*color, vec_scale(spec_lum, lgt->color));
	}
}

t_vec			trace_ray_to_light(t_env *env, t_ray *ray)
{
	t_lgt		*tmp;
	t_vec		color;

	tmp = env->lgt;
	color = vec_scale(env->amb.ratio, env->amb.color);
	while (tmp)
	{
		compute_lgt(env, tmp, ray, &color);
		tmp = tmp->next;
	}
	ray->color.x = ray->color.x / MAX_RGB;
	ray->color.y = ray->color.y / MAX_RGB;
	ray->color.z = ray->color.z / MAX_RGB;
	color = rescale_vec(vec_prod(ray->color, color), 0, MAX_RGB);
	return (color);
}
