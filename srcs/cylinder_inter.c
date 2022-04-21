/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/21 17:23:22 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	cyl_cap(t_vec poly, t_vec solve)
{
	if (fabs(poly.y + poly.x * solve.x) < solve.z)
		return (solve.x);
	return (0);
}

static float	cyl_col(t_cyl *cyl, t_ray *ray, t_ray obj, float angle[2])
{
	t_vec	poly;
	t_vec	solve;
	float	rp_cp_ch;

	rp_cp_ch = vec_dot(obj.dir, obj.pos);
	poly.x = angle[1] - angle[0] * angle[0];
	poly.y = angle[1] * vec_dot(obj.pos, ray->dir) - rp_cp_ch * angle[0];
	poly.z = angle[1] * vec_dot(obj.pos, obj.pos) - rp_cp_ch * rp_cp_ch - cyl->r * cyl->r * angle[1];
	solve.z = poly.y * poly.y - poly.x * poly.z;
	if (solve.z < 0.0)
		return (0);
	solve.z = sqrt(solve.z);
	solve.x = (-poly.y - solve.z) / poly.x;
	solve.y = rp_cp_ch + solve.x * angle[0];
	if (solve.y > 0.0 && solve.y < angle[1])
		return (solve.x);
	if (solve.y < 0.0)
		solve.x = - rp_cp_ch / angle[0];
	else
		solve.x = (angle[1] - rp_cp_ch) / angle[0];
	return (cyl_cap(poly, solve));
}

int		cylinder_intersect(t_cyl *cyl, t_ray *ray, float *t)
{
	t_ray		obj;
	float		angle[2];

	obj.dir = vec_sub(vec_scale(-cyl->h, cyl->dir), vec_scale(cyl->h, cyl->dir));
	angle[1] = vec_dot(obj.dir, obj.dir);
	obj.pos = vec_sub(ray->pos, vec_scale(cyl->h, cyl->dir));
	angle[0] = vec_dot(obj.dir, ray->dir);
	angle[1] = cyl_col(cyl, ray, obj, angle);
	if (angle[1] < EPSILON)
		return (0);
	*t = angle[1];
	return (1);
}