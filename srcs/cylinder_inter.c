/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/31 19:51:40 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double			solve_plane(t_ray *ray, t_v3 plane_p, t_v3 plane_nv)
{
	double	x;
	double	denom;

	denom = dot(plane_nv, ray->dir);
	if (denom == 0)
		return (INFINITY);
	x = (dot(plane_nv, vsubstract(plane_p, ray->pos))) / denom;
	return (x > 0 ? x : INFINITY);
}

static int		solve_cylinder(double x[2], t_p3 o, t_p3 d, t_figures *lst)
{
	t_p3	v;
	t_p3	u;
	double	a;
	double	b;
	double	c;

	v = scal_x_vec(dot(d, lst->fig.cy.nv), lst->fig.cy.nv);
	v = vsubstract(d, v);
	u = scal_x_vec(dot(vsubstract(o, lst->fig.cy.c), lst->fig.cy.nv),
													lst->fig.cy.nv);
	u = vsubstract(vsubstract(o, lst->fig.cy.c), u);
	a = dot(v, v);
	b = 2 * dot(v, u);
	c = dot(u, u) - pow(lst->fig.cy.r, 2);
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

static t_p3		calc_cy_normal(double x2[2], t_p3 o, t_p3 d, t_figures *lst)
{
	double	dist;
	double	x;

	if ((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
				&& x2[0] > EPSILON) && (lst->fig.cy.dist2 >= 0
				&& lst->fig.cy.dist2 <= lst->fig.cy.h && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? lst->fig.cy.dist1 : lst->fig.cy.dist2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
														&& x2[0] > EPSILON)
	{
		dist = lst->fig.cy.dist1;
		x = x2[0];
	}
	else
	{
		dist = lst->fig.cy.dist2;
		x = x2[1];
	}
	x2[0] = x;
	return (normalize(vsubstract(vsubstract(scal_x_vec(x, d),
			scal_x_vec(dist, lst->fig.cy.nv)), vsubstract(lst->fig.cy.c, o))));
}

static double	cy_intersection(t_p3 o, t_p3 d, t_p3 *normal, t_figures *lst)
{
	double	x2[2];

	if (solve_cylinder(x2, o, d, lst) == 0)
		return (INFINITY);
	lst->fig.cy.dist1 = dot(lst->fig.cy.nv, vsubstract(scal_x_vec(x2[0], d),
												vsubstract(lst->fig.cy.c, o)));
	lst->fig.cy.dist2 = dot(lst->fig.cy.nv, vsubstract(scal_x_vec(x2[1], d),
												vsubstract(lst->fig.cy.c, o)));
	if (!((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
					&& x2[0] > EPSILON) || (lst->fig.cy.dist2 >= 0
					&& lst->fig.cy.dist2 <= lst->fig.cy.h && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = calc_cy_normal(x2, o, d, lst);
	return (x2[0]);
}

static double	caps_intersection(t_ray *ray, t_cyl *cyl)
{
	double	id1;
	double	id2;
	t_v3	ip1;
	t_v3	ip2;
	t_v3	c2;

	c2 = v_add(cyl->pos, v_multi(cyl->h, cyl->dir));
	id1 = solve_plane(ray, cyl->pos, cyl->dir);
	id2 = solve_plane(ray, c2, cyl->dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = vadd(o, scal_x_vec(id1, d));
		ip2 = vadd(o, scal_x_vec(id2, d));
		if ((id1 < INFINITY && distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
				&& (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY
						&& distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
			return (id1);
		else if (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r)
			return (id2);
		return (INFINITY);
	}
	return (INFINITY);
}

double			cylinder_intersection(t_ray *ray, t_cyl *cyl)
{
	double	cylinder_inter;
	double	caps_inter;
	t_v3	cy_normal;

	cylinder_inter = cy_intersection(ray, &cy_normal, cyl);
	caps_inter = caps_intersection(ray, cyl);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			ray->normal = cy_normal;
			return (cylinder_inter);
		}
		ray->normal = cyl->dir;
		return (caps_inter);
	}
	return (INFINITY);
}