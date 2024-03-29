/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:32:20 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 19:24:23 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*init_object(t_env *env)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		exit_error(env, ERRNO_TO_STR);
	obj->data = NULL;
	obj->next = NULL;
	return (obj);
}

t_vec	get_obj_color(t_obj *obj)
{
	if (obj->id == SPHERE)
		return (((t_sph *)(obj->data))->color);
	else if (obj->id == PLANE)
		return (((t_pla *)(obj->data))->color);
	else if (obj->id == CYLINDER)
		return (((t_cyl *)(obj->data))->color);
	else if (obj->id == TRIANGLE)
		return (((t_tri *)(obj->data))->color);
	return (v_init(0, 0, 0, 0));
}

void	get_obj_normal(t_obj *obj, t_ray *ray)
{
	if (obj->id == SPHERE)
		ray->normal = get_sph_normal((t_sph *)(obj->data), ray);
	else if (obj->id == PLANE)
		ray->normal = ((t_pla *)(obj->data))->dir;
	else if (obj->id == CYLINDER)
		ray->normal = get_cyl_normal((t_cyl *)(obj->data), ray);
	else if (obj->id == TRIANGLE)
		ray->normal = get_tri_normal((t_tri *)(obj->data));
}

t_vec	*get_obj_pos(t_obj *obj)
{
	t_vec	*pos;

	pos = NULL;
	if (obj->id == SPHERE)
		pos = &(((t_sph *)(obj->data))->pos);
	else if (obj->id == PLANE)
		pos = &(((t_pla *)(obj->data))->pos);
	else if (obj->id == CYLINDER)
		pos = &(((t_cyl *)(obj->data))->pos);
	return (pos);
}

t_vec	*get_obj_dir(t_obj *obj)
{		
	t_vec	*dir;

	dir = NULL;
	if (obj->id == PLANE)
		dir = &(((t_pla *)(obj->data))->dir);
	else if (obj->id == CYLINDER)
		dir = &(((t_cyl *)(obj->data))->dir);
	return (dir);
}
