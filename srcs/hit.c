/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:06:50 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/21 18:13:00 by tamigore         ###   ########.fr       */
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

int		hit_objs(t_obj *obj, t_ray *ray, float *t, t_obj *closer)
{
	int ret;
	t_obj *tmp;
	int i;
	float dist;
	
	dist = 1.0 /0.0;
	i = 0;
	tmp = obj;
	ret = 0;
	while (tmp)
	{
		i++;
		ret += hit_obj(tmp, ray, t);
		if (dist > *t)
		{
			dist = *t;
			closer = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

int			hit_obj(t_obj *obj, t_ray *ray, float *t)
{
	int		hit;

	hit = 0;
	if (obj->id == SPHERE)
		hit = sphere_intersect((t_sph *)obj->data, ray, t);
	else if (obj->id == PLANE)
		hit = plane_intersect((t_pla *)obj->data, ray, t);
	else if (obj->id == CYLINDER)
		hit = cylinder_intersect((t_cyl *)obj->data, ray, t);
	else if (obj->id == TRIANGLE)
		hit = triangle_intersect((t_tri *)obj->data, ray, t);
	return (hit);
}
