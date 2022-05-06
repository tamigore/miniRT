/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:28:44 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:51:21 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	append_obj(t_obj **objs, t_obj *new_obj)
{
	t_obj	*tmp;

	if (!objs || !new_obj)
		return ;
	tmp = *objs;
	if (*objs)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
	}
	else
		*objs = new_obj;
}

void	get_sphere(t_env *env)
{
	t_obj	*obj;

	(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = SPHERE;
	obj->data = malloc(sizeof(t_sph));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	get_spher_plus(env, obj);
	if (!check_val(((t_sph *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_sph *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_sph *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (!check_val(((t_sph *)(obj->data))->pos.x, -INFINITY, INFINITY)
		|| !check_val(((t_sph *)(obj->data))->pos.y, -INFINITY, INFINITY)
		|| !check_val(((t_sph *)(obj->data))->pos.z, -INFINITY, INFINITY)
		|| fabs(((t_sph *)(obj->data))->r) == INFINITY)
		exit_error(env, DOUBLE_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}

void	get_plane(t_env *env)
{
	t_obj	*obj;

	(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = PLANE;
	obj->data = malloc(sizeof(t_pla));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	get_plane_plus(env, obj);
	if (!check_val(((t_pla *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_pla *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_pla *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (!check_val(((t_pla *)(obj->data))->pos.x, -INFINITY, INFINITY)
		|| !check_val(((t_pla *)(obj->data))->pos.y, -INFINITY, INFINITY)
		|| !check_val(((t_pla *)(obj->data))->pos.z, -INFINITY, INFINITY)
		|| !check_vec((((t_pla *)(obj->data))->dir), -1, 1))
		exit_error(env, DOUBLE_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}

void	get_cylinder(t_env *env)
{
	t_obj	*obj;

	(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = CYLINDER;
	obj->data = malloc(sizeof(t_cyl));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	get_cyliner_plus(env, obj);
	if (!check_val(((t_cyl *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_cyl *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_cyl *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (!check_vec(((t_cyl *)(obj->data))->pos, -INFINITY, INFINITY)
		|| !check_vec(((t_cyl *)(obj->data))->dir, -1, 1)
		|| fabs(((t_cyl *)(obj->data))->r) == INFINITY
		|| fabs(((t_cyl *)(obj->data))->h) == INFINITY)
		exit_error(env, DOUBLE_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}

void	get_triangle(t_env *env)
{
	t_obj	*obj;

	(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = TRIANGLE;
	obj->data = malloc(sizeof(t_tri));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	get_triangle_plus(env, obj);
	if (!check_val(((t_tri *)(obj->data))->p1.x, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p1.y, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p1.z, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p2.x, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p2.y, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p2.z, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p3.x, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p3.y, -INFINITY, INFINITY)
		|| !check_val(((t_tri *)(obj->data))->p3.z, -INFINITY, INFINITY))
		exit_error(env, DOUBLE_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}
