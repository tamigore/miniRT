/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:37:55 by tamigore          #+#    #+#             */
/*   Updated: 2021/02/11 17:44:40 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			sphere_intersect(t_sph *sph, t_ray *ray, double *t)
{
	double	t0;
	double	t1;
	t_v3	coef;
	t_v3	L;

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

int			cylinder_intersect(t_cyl *cyl, t_ray *ray, double *t)
{
	t_v3	coef;
	t_v3	oc;
	t_v3	dir;
	t_v3	ocdir;

	oc = v_sub(ray->pos, cyl->pos);
	dir = v_sub(ray->dir, v_multi(v_dot(ray->dir, cyl->dir), cyl->dir));
	ocdir = v_sub(oc, v_multi(v_dot(oc, cyl->dir), cyl->dir));
	coef.x = v_dot(dir, dir);
	coef.y = 2 * v_dot(dir, v_sub(dir, ocdir));
	coef.z = v_dot(v_sub(dir, ocdir), v_sub(dir, ocdir)) - (cyl->d * cyl->d);
	return (solve_cylinder(cyl, ray, coef, t));
}

int			plane_intersect(t_pla *pla, t_ray *ray, double *t)
{
	return (hit_plane(pla->pos, pla->dir, ray, t));
}

int			square_intersect(t_sqr *sqr, t_ray *ray, double *t)
{
	t_v3	hit;
	t_v3	dist;
	double	border;

	if (hit_plane(sqr->pos, sqr->dir, ray, t))
	{
		hit = v_add(ray->pos, v_multi(*t, ray->dir));
		dist = v_sub(hit, sqr->pos);
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
	t_v3	hit;
	t_v3	normal;

	normal = get_tri_normal(tri);
	if (hit_plane(tri->p1, normal, ray, t))
	{
		hit = v_add(ray->pos, v_multi(*t, ray->dir));
		return (check_edge(tri->p2, tri->p1, hit, normal))
		&& (check_edge(tri->p3, tri->p2, hit, normal))
		&& (check_edge(tri->p1, tri->p3, hit, normal));
	}
	return (0);
}
