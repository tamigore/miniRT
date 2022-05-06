/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:28:44 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 19:24:08 by tamigore         ###   ########.fr       */
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

	if (!ft_strncmp(env->sceen, SPH_ID, ID_OBJ_LEN))
		(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = SPHERE;
	obj->data = malloc(sizeof(t_sph));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	((t_sph *)(obj->data))->pos.x = str_to_double(env);
	((t_sph *)(obj->data))->pos.y = str_to_double(env);
	((t_sph *)(obj->data))->pos.z = str_to_double(env);
	((t_sph *)(obj->data))->r = str_to_double(env) / 2;
	((t_sph *)(obj->data))->color.x = str_to_unsigned(env);
	((t_sph *)(obj->data))->color.y = str_to_unsigned(env);
	((t_sph *)(obj->data))->color.z = str_to_unsigned(env);
	if (!check_val(((t_sph *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_sph *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_sph *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (fabs(((t_sph *)(obj->data))->pos.x) == INFINITY
		|| fabs(((t_sph *)(obj->data))->pos.y) == INFINITY
		|| fabs(((t_sph *)(obj->data))->pos.z) == INFINITY
		|| fabs(((t_sph *)(obj->data))->r) == INFINITY)
		exit_error(env, double_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}

void	get_plane(t_env *env)
{
	t_obj	*obj;

	if (!ft_strncmp(env->sceen, PLA_ID, ID_OBJ_LEN))
		(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = PLANE;
	obj->data = malloc(sizeof(t_pla));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	((t_pla *)(obj->data))->pos.x = str_to_double(env);
	((t_pla *)(obj->data))->pos.y = str_to_double(env);
	((t_pla *)(obj->data))->pos.z = str_to_double(env);
	((t_pla *)(obj->data))->dir.x = str_to_double(env);
	((t_pla *)(obj->data))->dir.y = str_to_double(env);
	((t_pla *)(obj->data))->dir.z = str_to_double(env);
	((t_pla *)(obj->data))->color.x = str_to_unsigned(env);
	((t_pla *)(obj->data))->color.y = str_to_unsigned(env);
	((t_pla *)(obj->data))->color.z = str_to_unsigned(env);
	if (!check_val(((t_pla *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_pla *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_pla *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (fabs(((t_pla *)(obj->data))->pos.x) == INFINITY
		|| fabs(((t_pla *)(obj->data))->pos.y) == INFINITY
		|| fabs(((t_pla *)(obj->data))->pos.z) == INFINITY
		|| !check_vec(((t_pla *)(obj->data))->dir))
		exit_error(env, double_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}

void	get_cylinder(t_env *env)
{
	t_obj	*obj;

	if (!ft_strncmp(env->sceen, CYL_ID, ID_OBJ_LEN))
		(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = CYLINDER;
	obj->data = malloc(sizeof(t_cyl));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	((t_cyl *)(obj->data))->pos.x = str_to_double(env);
	((t_cyl *)(obj->data))->pos.y = str_to_double(env);
	((t_cyl *)(obj->data))->pos.z = str_to_double(env);
	((t_cyl *)(obj->data))->dir.x = str_to_double(env);
	((t_cyl *)(obj->data))->dir.y = str_to_double(env);
	((t_cyl *)(obj->data))->dir.z = str_to_double(env);
	((t_cyl *)(obj->data))->r = str_to_double(env) / 2;
	((t_cyl *)(obj->data))->h = str_to_double(env);
	((t_cyl *)(obj->data))->color.x = str_to_unsigned(env);
	((t_cyl *)(obj->data))->color.y = str_to_unsigned(env);
	((t_cyl *)(obj->data))->color.z = str_to_unsigned(env);
	if (!check_val(((t_cyl *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_cyl *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_cyl *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (fabs(((t_cyl *)(obj->data))->pos.x) == INFINITY
		|| fabs(((t_cyl *)(obj->data))->pos.y) == INFINITY
		|| fabs(((t_cyl *)(obj->data))->pos.z) == INFINITY
		|| !check_vec(((t_cyl *)(obj->data))->dir)
		|| fabs(((t_cyl *)(obj->data))->r) == INFINITY
		|| fabs(((t_cyl *)(obj->data))->h) == INFINITY)
		exit_error(env, double_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}

void	get_triangle(t_env *env)
{
	t_obj	*obj;

	if (!ft_strncmp(env->sceen, CYL_ID, ID_OBJ_LEN))
		(env->sceen) += ID_OBJ_LEN;
	obj = init_object(env);
	obj->id = TRIANGLE;
	obj->data = malloc(sizeof(t_tri));
	if (!obj->data)
	{
		free(obj);
		exit_error(env, ERRNO_TO_STR);
	}
	((t_tri *)(obj->data))->p1.x = str_to_double(env);
	((t_tri *)(obj->data))->p1.y = str_to_double(env);
	((t_tri *)(obj->data))->p1.z = str_to_double(env);
	((t_tri *)(obj->data))->p2.x = str_to_double(env);
	((t_tri *)(obj->data))->p2.y = str_to_double(env);
	((t_tri *)(obj->data))->p2.z = str_to_double(env);
	((t_tri *)(obj->data))->p3.x = str_to_double(env);
	((t_tri *)(obj->data))->p3.y = str_to_double(env);
	((t_tri *)(obj->data))->p3.z = str_to_double(env);
	((t_tri *)(obj->data))->color.x = str_to_unsigned(env);
	((t_tri *)(obj->data))->color.y = str_to_unsigned(env);
	((t_tri *)(obj->data))->color.z = str_to_unsigned(env);
	if (!check_val(((t_tri *)(obj->data))->color.x, 0, 255)
		|| !check_val(((t_tri *)(obj->data))->color.y, 0, 255)
		|| !check_val(((t_tri *)(obj->data))->color.z, 0, 255))
		exit_error(env, COLOR_FMT);
	if (fabs(((t_tri *)(obj->data))->p1.x) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p1.y) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p1.z) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p2.x) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p2.y) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p2.z) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p3.x) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p3.y) == INFINITY
		|| fabs(((t_tri *)(obj->data))->p3.z) == INFINITY)
		exit_error(env, double_FMT);
	env->nb_obj++;
	append_obj(&(env->obj), obj);
}
