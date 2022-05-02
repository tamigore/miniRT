/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_lgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:20:47 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 13:23:25 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		is_in_shadow(t_env *env, t_ray *ray, t_vec lgt_dir)
{
	t_obj		*tmp;
	t_ray		shadow_ray;
	double		t;

	t = v_len(lgt_dir);
	set_ray(&shadow_ray, ray->hit, v_norm(lgt_dir), t);
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

static double	get_specular(t_ray *ray, t_lgt *lgt, t_vec lgt_dir, double pov)
{
	t_vec	rev_dir;
	t_vec	reflect;
	double	coef;

	coef = 1;
	rev_dir = v_scale(-1, ray->dir);
	reflect = v_sub(v_scale((2 * pov), ray->normal), v_norm(lgt_dir));
	if (v_dot(reflect, rev_dir) > 0.0)
		coef = lgt->ratio * pow(v_cos(reflect, rev_dir), 70);
	return (coef);
}

static void		compute_lgt(t_env *env, t_lgt *lgt, t_ray *ray, t_vec *color)
{
	t_vec		lgt_dir;
	double		pov;
	double		lum;
	double		spec_lum;

	lgt_dir = v_norm(v_sub(lgt->pos, ray->hit));
	pov = v_dot(ray->normal, lgt_dir);
	lum = 0;
	spec_lum = 0;
	if (!is_in_shadow(env, ray, lgt_dir) && pov > 0.0)
	{
		lum = lgt->ratio * v_cos(ray->normal, lgt_dir);
		*color = v_scale(lum, lgt->color);
		spec_lum = get_specular(ray, lgt, lgt_dir, pov);
		*color = v_add(*color, v_scale(spec_lum, lgt->color));
	}
}

t_vec			trace_ray_to_light(t_env *env, t_ray *ray)
{
	t_lgt		*tmp;
	t_vec		color;

	tmp = env->lgt;
	color = v_scale(env->amb.ratio, env->amb.color);
	while (tmp)
	{
		compute_lgt(env, tmp, ray, &color);
		tmp = tmp->next;
	}
	ray->color.x = ray->color.x / MAX_RGB;
	ray->color.y = ray->color.y / MAX_RGB;
	ray->color.z = ray->color.z / MAX_RGB;
	color = rescale_vec(v_prod(ray->color, color), 0, MAX_RGB);
	return (color);
}
