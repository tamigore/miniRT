/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:06:50 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 17:45:19 by tamigore         ###   ########.fr       */
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
