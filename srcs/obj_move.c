/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:28:09 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 19:30:38 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_obj2(char c, t_obj *obj, int mv)
{
	if (c == 'x')
	{
		((t_tri *)(obj->data))->p1.x += mv;
		((t_tri *)(obj->data))->p2.x += mv;
		((t_tri *)(obj->data))->p3.x += mv;
	}
	else if (c == 'y')
	{
		((t_tri *)(obj->data))->p1.y += mv;
		((t_tri *)(obj->data))->p2.y += mv;
		((t_tri *)(obj->data))->p3.y += mv;
	}
	else if (c == 'z')
	{
		((t_tri *)(obj->data))->p1.z += mv;
		((t_tri *)(obj->data))->p2.z += mv;
		((t_tri *)(obj->data))->p3.z += mv;
	}
}

void	move_obj(t_obj *obj, char c, int mv)
{
	t_vec	*pos;

	pos = get_obj_pos(obj);
	if (pos)
	{
		if (c == 'x')
			pos->x += mv;
		else if (c == 'y')
			pos->y += mv;
		else if (c == 'z')
			pos->z += mv;
		return ;
	}
	move_obj2(c, obj, mv);
}

void	rotate_obj(t_obj *obj, double deg)
{
	t_vec	*dir;
	t_mat	rota;

	dir = get_obj_dir(obj);
	if (v_dot(*dir, v_init(1, 0, 0, 0)) == 0)
		rota = rotx_mat_init(deg);
	else if (v_dot(*dir, v_init(0, 1, 0, 0)) == 0)
		rota = roty_mat_init(deg);
	else
		rota = rotz_mat_init(deg);
	*dir = mat_mult_vec(rota, *dir);
}

void	obj_move(int keycode, t_env *env)
{
	if (keycode == 65432)
		move_obj(env->hit_obj, 'x', OBJ_MOVE);
	if (keycode == 65430)
		move_obj(env->hit_obj, 'x', -OBJ_MOVE);
	if (keycode == 65431)
		move_obj(env->hit_obj, 'y', OBJ_MOVE);
	if (keycode == 65437)
		move_obj(env->hit_obj, 'y', -OBJ_MOVE);
	if (keycode == 65453)
		move_obj(env->hit_obj, 'z', -OBJ_MOVE);
	if (keycode == 65451)
		move_obj(env->hit_obj, 'z', OBJ_MOVE);
	if (keycode == 65434)
		rotate_obj(env->hit_obj, -OBJ_MOVE);
	if (keycode == 65429)
		rotate_obj(env->hit_obj, OBJ_MOVE);
}
