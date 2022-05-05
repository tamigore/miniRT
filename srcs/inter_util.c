/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:40:08 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 18:28:35 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	solve_quadratic(t_vec coef, double *x0, double *x1)
{
	double	delta;
	double	q;

	delta = coef.y * coef.y - 4 * coef.x * coef.z;
	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		*x0 = -0.5 * coef.y / coef.x;
		*x1 = -0.5 * coef.y / coef.x;
	}
	else
	{
		q = -0.5 * (coef.y - sqrt(delta));
		if (coef.y > 0)
			q = -0.5 * (coef.y + sqrt(delta));
		*x0 = q / coef.x;
		*x1 = coef.z / q;
	}
	if (*x0 > *x1)
		swap(x0, x1);
	return (1);
}

int	hit_plane(t_vec pos, t_vec dir, t_ray *ray, double *t)
{
	double	denom;

	denom = v_dot(dir, ray->dir);
	if (denom == 0)
		return (0);
	if (fabs(denom) > EPSILON)
	{
		*t = v_dot(dir, v_sub(pos, ray->pos)) / denom;
		if (*t >= EPSILON)
			return (1);
		else
			*t = INFINITY;
	}
	return (0);
}

int	check_edge(t_vec to, t_vec from, t_vec hit, t_vec normal)
{
	t_vec	edge;
	t_vec	vec;

	edge = v_sub(to, from);
	vec = v_sub(hit, from);
	return (v_dot(normal, v_cross(edge, vec)) >= EPSILON);
}
