/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:37:55 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/13 17:35:12 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Le sphere intersect de Tadeo est le best le tiens pue la merde XD

int			sphere_intersect(t_sph *sph, t_ray *ray, double *t)
{
	double	t0;
	double	t1;
	t_vec	coef;
	t_vec	L;

	L = vec_sub(ray->pos, sph->pos);
	coef.x = vec_dot(ray->dir, ray->dir);
	coef.y = 2 * vec_dot(ray->dir, L);
	coef.z = vec_dot(L, L) - (sph->r * sph->r);
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

int			square_intersect(t_sqr *sqr, t_ray *ray, double *t)
{
	t_vec	hit;
	t_vec	dist;
	double	border;

	if (hit_plane(sqr->pos, sqr->dir, ray, t))
	{
		hit = vec_add(ray->pos, vec_scale(*t, ray->dir));
		dist = vec_sub(hit, sqr->pos);
		border = sqr->side * 0.5;
		return (
			(fabs(dist.x) <= border)
			&& (fabs(dist.y) <= border)
			&& (fabs(dist.z) <= border));
	}
	return (0);
}

int			triangle_intersect(t_tri *tri, t_ray *ray, double *t)
{
	t_vec	hit;
	t_vec	normal;

	normal = get_tri_normal(tri);
	if (hit_plane(tri->p1, normal, ray, t))
	{
		hit = vec_add(ray->pos, vec_scale(*t, ray->dir));
		return (check_edge(tri->p2, tri->p1, hit, normal))
		&& (check_edge(tri->p3, tri->p2, hit, normal))
		&& (check_edge(tri->p1, tri->p3, hit, normal));
	}
	return (0);
}
