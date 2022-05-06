/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:38:41 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:49:18 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_spher_plus(t_env *env, t_obj *obj)
{
	((t_sph *)(obj->data))->pos.x = str_to_double(env);
	((t_sph *)(obj->data))->pos.y = str_to_double(env);
	((t_sph *)(obj->data))->pos.z = str_to_double(env);
	((t_sph *)(obj->data))->r = str_to_double(env) / 2;
	((t_sph *)(obj->data))->color.x = str_to_unsigned(env);
	((t_sph *)(obj->data))->color.y = str_to_unsigned(env);
	((t_sph *)(obj->data))->color.z = str_to_unsigned(env);
}

void	get_plane_plus(t_env *env, t_obj *obj)
{
	((t_pla *)(obj->data))->pos.x = str_to_double(env);
	((t_pla *)(obj->data))->pos.y = str_to_double(env);
	((t_pla *)(obj->data))->pos.z = str_to_double(env);
	((t_pla *)(obj->data))->dir.x = str_to_double(env);
	((t_pla *)(obj->data))->dir.y = str_to_double(env);
	((t_pla *)(obj->data))->dir.z = str_to_double(env);
	((t_pla *)(obj->data))->color.x = str_to_unsigned(env);
	((t_pla *)(obj->data))->color.y = str_to_unsigned(env);
	((t_pla *)(obj->data))->color.z = str_to_unsigned(env);
}

void	get_cyliner_plus(t_env *env, t_obj *obj)
{
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
}

void	get_triangle_plus(t_env *env, t_obj *obj)
{
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
}
