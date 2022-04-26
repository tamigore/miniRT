/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/04/20 13:19:57 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int			key_handler(int keycode, t_env *env)
{
	printf("key code = %d\n", keycode);
	if (keycode == ESC_KEY)
		exit_sucess(env);
	if ((keycode >= 65361 && keycode <= 65438) || (keycode >= 32 && keycode <= 150))
		if (camera_move(keycode, env) == 0)
			return (0);
	if (keycode == 65432)
	{
		env->lgt->pos.x += 3;
		printf("6\n");
	}
	if (keycode == 65430)
	{
		env->lgt->pos.x -= 3;
		printf("4\n");
	}
	if (keycode == 65431)
	{
		env->lgt->pos.y += 3;
		printf("8\n");
	}
	if (keycode == 65437)
	{
		env->lgt->pos.y -= 3;
		printf("5\n");
	}
	if (keycode == 65453)
	{
		env->lgt->pos.z -= 3;
		printf("-\n");
	}
	if (keycode == 65451)
	{
		env->lgt->pos.z += 3;
		printf("+\n");
	}
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
	env->hit_obj = trace_objs(env->obj, &ray);
    if (env->hit_obj != NULL)
        print_obj(env->hit_obj);
    return (1);
}

void		graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y, "miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	mlx_mouse_hook(env->win, mouse_hook, env);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_handler, env);
	mlx_hook(env->win, LEAVENOTIFY, 0, close_program, env);
	mlx_loop(env->mlx);
}
