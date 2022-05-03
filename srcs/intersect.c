/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:37:55 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/03 18:44:01 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			sphere_intersect(t_sph *sph, t_ray *ray, double *t)
{
	double	t0;
	double	t1;
	t_vec	coef;
	t_vec	L;

	L = v_sub(ray->pos, sph->pos);
	coef.x = v_dot(ray->dir, ray->dir);
	coef.y = 2 * v_dot(ray->dir, L);
	coef.z = v_dot(L, L) - (sph->r * sph->r);
	if (!solve_quadratic(coef, &t0, &t1))
		return (0);
	if (t0 > t1 && t1 > EPSILON)
		swap(&t0, &t1);
	if (t0 > INFINITY || t0 < EPSILON)
		return (0);
	*t = t0;
	return (1);
}

int			plane_intersect(t_pla *pla, t_ray *ray, double *t)
{
	return (hit_plane(pla->pos, pla->dir, ray, t));
}

int			triangle_intersect(t_tri *tri, t_ray *ray, double *t)
{
	t_vec	hit;
	t_vec	normal;

	normal = get_tri_normal(tri);
	if (hit_plane(tri->p1, normal, ray, t))
	{
		hit = v_add(ray->pos, v_scale(*t, ray->dir));
		return (check_edge(tri->p2, tri->p1, hit, normal))
		&& (check_edge(tri->p3, tri->p2, hit, normal))
		&& (check_edge(tri->p1, tri->p3, hit, normal));
	}
	return (0);
}


