/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_lgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:20:47 by tamigore          #+#    #+#             */
/*   Updated: 2021/03/17 18:02:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		is_in_shadow(t_obj *objs, t_ray *ray, t_v3 lgt_dir)
{
	t_obj		*tmp;
	t_ray		shadow_ray;
	double		t;

	t = v_len(lgt_dir);
	set_ray(&shadow_ray, ray->hit, v_norm(lgt_dir), t);
	tmp = objs;
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

static double	get_specular(t_ray *ray, t_lgt *lgt, t_v3 lgt_dir, double pov)
{
	t_v3	rev_dir;
	t_v3	reflect;
	double	coef;

	coef = 1;
	rev_dir = v_multi(-1, ray->dir);
	reflect = v_sub(v_multi((2 * pov), ray->normal), v_norm(lgt_dir));
	if (v_dot(reflect, rev_dir) > 0.0)
		coef = lgt->ratio * pow(v_cos(reflect, rev_dir), 70);
	return (coef);
}

static void		compute_lgt(t_obj *obj, t_lgt *lgt, t_ray *ray, t_v3 *color)
{
	t_v3		lgt_dir;
	double		pov;
	double		lum;
	double		spec_lum;

	lgt_dir = v_norm(v_sub(lgt->pos, ray->hit));
	pov = v_dot(ray->normal, v_norm(lgt_dir));
	lum = 0;
	spec_lum = 0;
	if (!is_in_shadow(obj, ray, lgt_dir) && pov > 0.0)
	{
		lum = lgt->ratio * v_cos(ray->normal, lgt_dir);
		printf("lum : %f\n", lum);
		*color = v_multi(lum, lgt->color);
		spec_lum = get_specular(ray, lgt, lgt_dir, pov);
		printf("spec lum : %f\n", spec_lum);
		*color = v_add(*color, v_multi(spec_lum, lgt->color));
	}
}

t_v3			trace_ray_to_light(t_env *env, t_ray *ray)
{
	t_lgt		*tmp;
	t_v3		color;

	tmp = env->lgt;
	color = v_multi(env->amb.ratio, env->amb.color);
	while (tmp)
	{
		compute_lgt(env->obj, tmp, ray, &color);
		tmp = tmp->next;
	}
	return (rescale_vec(v_prod(ray->color, color), 0, MAX_RGB));
}
