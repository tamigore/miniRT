/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/05/03 19:02:11 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define OBJ_MOVE 1

int			close_program(t_env *env)
{
	exit_sucess(env);
	exit(0);
	return (0);
}

static int	camera_move(int keycode, t_env *env)
{
	if (keycode == SP_KEY)
	{
		printf("Next camera\n");
		env->cam = env->cam->next;
		mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
		return (0);
	}
	move_left_right(env, keycode);
	move_forward_backward(env, keycode);
	move_up_down(env, keycode);
	rotate_1(env, keycode);
	rotate_2(env, keycode);
	return (1);
}

void		move_obj(t_obj * obj, char c, int mv)
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

void		obj_move(int keycode, t_env *env)
{
	if (keycode == 65432)
	{
		move_obj(env->hit_obj, 'x', OBJ_MOVE);
		printf("6\n");
	}
	if (keycode == 65430)
	{
		move_obj(env->hit_obj, 'x', -OBJ_MOVE);
		printf("4\n");
	}
	if (keycode == 65431)
	{
		move_obj(env->hit_obj, 'y', OBJ_MOVE);
		printf("8\n");
	}
	if (keycode == 65437)
	{
		move_obj(env->hit_obj, 'y', -OBJ_MOVE);
		printf("5\n");
	}
	if (keycode == 65453)
	{
		move_obj(env->hit_obj, 'z', -OBJ_MOVE);
		printf("-\n");
	}
	if (keycode == 65451)
	{
		move_obj(env->hit_obj, 'z', OBJ_MOVE);
		printf("+\n");
	}
	if (keycode == 65434)
	{
		rotate_obj(env->hit_obj, -OBJ_MOVE);
	}
	if (keycode == 65429)
	{
		rotate_obj(env->hit_obj, OBJ_MOVE);
	}
}

int			key_handler(int keycode, t_env *env)
{
	printf("key code = %d\n", keycode);
	if (keycode == ESC_KEY)
		exit_sucess(env);
	if ((keycode >= 65361 && keycode <= 65438) || (keycode >= 32 && keycode <= 150))
		if (camera_move(keycode, env) == 0)
			return (0);
	if (keycode >= 65429 && keycode <= 65453)
		if (env->hit_obj)
			obj_move(keycode, env);
	trace_ray(env);
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	return (0);
}

int    mouse_hook(int button, int x, int y, t_env *env)
{
    (void)button;
    t_ray ray;
    t_obj *tmp;

    tmp = env->obj;
    printf("click x : %d , y : %d\n", x, y);
    ray = canvas2view(env, env->cam, x, y);
	env->hit_obj = hit_objs(env->obj, &ray);
    if (env->hit_obj != NULL)
	{
		ray.hit = v_add(ray.pos, v_scale(ray.t - EPSILON, ray.dir));
		print_obj(env->hit_obj);
		printf("ray.hit : %f.x | %f.y | %f.z\n", ray.hit.x, ray.hit.y, ray.hit.z);
	}
	return (1);
}

void		graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y, "miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	mlx_mouse_hook(env->win, mouse_hook, env);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_handler, env);
	mlx_hook(env->win, 0, 17, close_program, env);
	mlx_loop(env->mlx);
}
