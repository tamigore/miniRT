/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:37:55 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 19:13:14 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			sphere_intersect(t_sph *sph, t_ray *ray, float *t)
{
	float	t0;
	float	t1;
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

int			plane_intersect(t_pla *pla, t_ray *ray, float *t)
{
	return (hit_plane(pla->pos, pla->dir, ray, t));
}

int			square_intersect(t_sqr *sqr, t_ray *ray, float *t)
{
	t_vec	hit;
	t_vec	dist;
	float	border;
	t_vec	up;
	t_vec	right;

	right = get_orthogonal(sqr->dir);
	up = vec_cross(sqr->dir, right);
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
	else if (hit_plane(sqr->pos, right, ray, t))
	{
		hit = vec_add(ray->pos, vec_scale(*t, ray->dir));
		dist = vec_sub(hit, sqr->pos);
		border = sqr->side * 0.5;
		return (
			(fabs(dist.x) <= border)
			&& (fabs(dist.y) <= border)
			&& (fabs(dist.z) <= border));
	}
	else if (hit_plane(sqr->pos, up, ray, t))
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

int			triangle_intersect(t_tri *tri, t_ray *ray, float *t)
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
