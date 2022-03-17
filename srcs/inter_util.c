/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanter <dasanter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:40:08 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/14 17:28:09 by dasanter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			solve_quadratic(t_v3 coef, double *x0, double *x1)
{
	double	delta;
	double	q;

	delta = coef.y * coef.y - 4 * coef.x * coef.z;
	if (delta < 0)
		return 0;
	else if (delta == 0)
	{
		*x0 = - 0.5 * coef.y / coef.x;
		*x1 = - 0.5 * coef.y / coef.x;
	}
	else
	{
		q = (coef.y > 0) ? -0.5 * (coef.y + sqrt(delta)) :
			-0.5 * (coef.y - sqrt(delta));
		*x0 = q / coef.x;
		*x1 = coef.z / q;
	}
	if (*x0 > *x1)
		swap(x0, x1);
	return (1);
}

static int	inside_cyl(t_cyl *cyl, t_ray *ray, double t)
{
	t_v3	hit;
	t_v3	bot;
	t_v3	top;

	hit = v_add(ray->pos, v_multi(t, ray->dir));
	bot = v_sub(hit, cyl->pos);
	top = v_sub(hit, v_add(cyl->pos, v_multi(cyl->h, cyl->dir)));
	return ((v_dot(cyl->dir, bot) > 0)
		&& (v_dot(cyl->dir, top) < 0));
}

int			solve_cylinder(t_cyl *cyl, t_ray *ray, t_v3 coef, double *t)
{
	double	root1;
	double	root2;
	int		hit;

	hit = 0;
	if (solve_quadratic(coef, &root1, &root2))
	{
		if (root1 > EPSILON && inside_cyl(cyl, ray, root1))
		{
			hit = 1;
			*t = root1;
		}
		if (root2 > EPSILON && inside_cyl(cyl, ray, root2))
		{
			hit = 1;
			if (root2 > root1)
				*t = root2;
		}
	}
	return (hit);
}

int			hit_plane(t_v3 pos, t_v3 dir, t_ray *ray, double *t)
{
	double	denom;
	t_v3	p;

	denom = v_dot(dir, ray->dir);
	if (denom == 0)
		return (0);
	if (fabs(denom) > EPSILON)
	{
		p = v_sub(pos, ray->pos);
		*t = v_dot(p, dir) / denom;
		if (*t >= EPSILON)
			return (1);
	}
	return (0);
}

int			check_edge(t_v3 to, t_v3 from, t_v3 hit, t_v3 normal)
{
	t_v3	edge;
	t_v3	vec;

	edge = v_sub(to, from);
	vec = v_sub(hit, from);
	return (v_dot(normal, v_cross(edge, vec)) >= 0.0);
}
