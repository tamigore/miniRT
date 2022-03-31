/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:06:50 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/31 19:19:36 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj		*trace_objs(t_obj *obj, t_ray *ray)
{
	t_obj	*tmp;
	t_obj	*hit;

	hit = NULL;
	tmp = obj;
	while (tmp)
	{
		if (tmp->id == SPHERE)
			if (trace_sph((t_sph *)(tmp->data), ray))
				hit = tmp;
		if (tmp->id == PLANE)
			if (trace_pla((t_pla *)(tmp->data), ray))
				hit = tmp;
		if (tmp->id == SQUARE)
			if (trace_sqr((t_sqr *)(tmp->data), ray))
				hit = tmp;
		if (tmp->id == CYLINDER)
			if (trace_cyl((t_cyl *)(tmp->data), ray))
				hit = tmp;
		if (tmp->id == TRIANGLE)
			if (trace_tri((t_tri *)(tmp->data), ray))
				hit = tmp;
		tmp = tmp->next;
	}
	return (hit);
}

int			hit_obj(t_obj *obj, t_ray *ray, double *t)
{
	int		hit;

	hit = 0;
	if (obj->id == SPHERE)
		hit = sphere_intersect((t_sph *)obj->data, ray, t);
	else if (obj->id == PLANE)
		hit = plane_intersect((t_pla *)obj->data, ray, t);
	else if (obj->id == SQUARE)
		hit = square_intersect((t_sqr *)obj->data, ray, t);
	else if (obj->id == CYLINDER)
		hit = cylinder_intersect((t_cyl *)obj->data, ray, t);
	else if (obj->id == TRIANGLE)
		hit = triangle_intersect((t_tri *)obj->data, ray, t);
	return (hit);
}

//--------------------------------------------------------------------------
// Ray : P(t) = O + V * t
// Cylinder [O, D, r].
// point Q on cylinder if ((Q - O) x D)^2 = r^2
// Cylinder [A, B, r].
// Point P on infinite cylinder if ((P - A) x (B - A))^2 = r^2 * (B - A)^2
// expand : ((O - A) x (B - A) + t * (V x (B - A)))^2 = r^2 * (B - A)^2
// equation in the form (X + t * Y)^2 = d
// where : 
//  X = (O - A) x (B - A)//  Y = V x (B - A)
//  d = r^2 * (B - A)^2// expand the equation :
// t^2 * (Y . Y) + t * (2 * (X . Y)) + (X . X) - d = 0
// => second order equation in the form : a*t^2 + b*t + c = 0 where
// a = (Y . Y)// b = 2 * (X . Y)// c = (X . X) - d
//--------------------------------------------------------------------------
// Vector AB = (B - A);Vector AO = (O - A);Vector AOxAB = (AO ^ AB);
// cross productVector VxAB  = (V ^ AB); // cross productfloat  ab2 = (AB * AB);
// dot productfloat a      = (VxAB * VxAB);
// dot productfloat b      = 2 * (VxAB * AOxAB);
// dot productfloat c      = (AOxAB * AOxAB) - (r*r * ab2);
// solve second order equation : a*t^2 + b*t + c = 0