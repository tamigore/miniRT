/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/20 17:28:06 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float			solve_plane(t_ray *ray, t_vec plane_p, t_vec plane_nv)
{
	float	x;
	float	denom;

	denom = vec_dot(plane_nv, ray->dir);
	if (denom == 0)
		return (INFINITY);
	x = (vec_dot(plane_nv, vec_sub(plane_p, ray->pos))) / denom;
	return (x > 0 ? x : INFINITY);
}

static int		solve_cylinder(float x[2], t_ray *ray, t_cyl *cyl)
{
	t_vec	v;
	t_vec	u;
	float	a;
	float	b;
	float	c;

	v = vec_scale(vec_dot(ray->dir, cyl->dir), cyl->dir);
	v = vec_sub(ray->dir, v);
	u = vec_scale(vec_dot(vec_sub(ray->pos, cyl->pos), cyl->dir), cyl->dir);
	u = vec_sub(vec_sub(ray->dir, cyl->pos), u);
	a = vec_dot(v, v);
	b = 2 * vec_dot(v, u);
	c = vec_dot(u, u) - pow(cyl->r, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

static t_vec		calc_cy_normal(float x2[2], t_ray *ray, t_cyl *cyl)
{
	float	dist;
	float	x;

	if ((cyl->dist1 >= 0 && cyl->dist1 <= cyl->h
				&& x2[0] > EPSILON) && (cyl->dist2 >= 0
				&& cyl->dist2 <= cyl->h && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? cyl->dist1 : cyl->dist2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (cyl->dist1 >= 0 && cyl->dist1 <= cyl->h && x2[0] > EPSILON)
	{
		dist = cyl->dist1;
		x = x2[0];
	}
	else
	{
		dist = cyl->dist2;
		x = x2[1];
	}
	x2[0] = x;
	return (vec_norm(vec_sub(vec_sub(vec_scale(x, ray->dir), vec_scale(dist, cyl->dir)), vec_sub(cyl->pos, ray->pos))));
}

static float	cyl_intersect(t_ray *ray, t_vec *normal, t_cyl *cyl)
{
	float	x2[2];

	if (solve_cylinder(x2, ray, cyl) == 0)
		return (INFINITY);
	cyl->dist1 = vec_dot(cyl->dir, vec_sub(vec_scale(x2[0], ray->dir), vec_sub(cyl->pos, ray->pos)));
	cyl->dist2 = vec_dot(cyl->dir, vec_sub(vec_scale(x2[1], ray->dir), vec_sub(cyl->pos, ray->pos)));
	if (!((cyl->dist1 >= 0 && cyl->dist1 <= cyl->h
					&& x2[0] > EPSILON) || (cyl->dist2 >= 0
					&& cyl->dist2 <= cyl->h && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = calc_cy_normal(x2, ray, cyl);
	return (x2[0]);
}

static float	caps_intersect(t_ray *ray, t_cyl *cyl)
{
	float	id1;
	float	id2;
	t_vec	ip1;
	t_vec	ip2;
	t_vec	c2;

	c2 = vec_add(cyl->pos, vec_scale(cyl->h, cyl->dir));
	id1 = solve_plane(ray, cyl->pos, cyl->dir);
	id2 = solve_plane(ray, c2, cyl->dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = vec_add(ray->pos, vec_scale(id1, ray->dir));
		ip2 = vec_add(ray->pos, vec_scale(id2, ray->dir));
		if ((id1 < INFINITY && vec_len(vec_sub(cyl->pos, ip1)) <= cyl->r)
				&& (id2 < INFINITY && vec_len(vec_sub(c2, ip2)) <= cyl->r))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY
						&& vec_len(vec_sub(cyl->pos, ip1)) <= cyl->r)
			return (id1);
		else if (id2 < INFINITY && vec_len(vec_sub(c2, ip2)) <= cyl->r)
			return (id2);
		return (INFINITY);
	}
	return (INFINITY);
}

int			cylinder_intersect(t_cyl *cyl, t_ray *ray, float *t)
{
	float	cylinder_inter;
	float	caps_inter;
	t_vec	cy_normal;

	cylinder_inter = cyl_intersect(ray, &cy_normal, cyl);
	caps_inter = caps_intersect(ray, cyl);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter && cylinder_inter < INFINITY)
		{
			// ray->normal = cy_normal;
			*t = cylinder_inter;
			printf("| cyl_inter = %f ", cylinder_inter);
			return (1);
		}
		else if (caps_inter < INFINITY)
		{
//			ray->normal = cyl->dir;
			*t = caps_inter;
			printf("| caps_inter = %f ", caps_inter);
			return (1);
		}
	}
	*t = 0;
	return (0);
}