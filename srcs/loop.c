/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/03/31 18:56:56 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			close_program(t_env *env)
{
	exit_sucess(env);
	exit(0);
	return (0);
}

int			key_handler(int keycode, t_env *env)
{
	printf("key code = %d\n", keycode);
	if (keycode == ESC_KEY)
		exit_sucess(env);
	if (keycode == SP_KEY)
	{
		printf("Next camera\n");
		env->cam = env->cam->next;
		mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
		return (0);
	}
	if (keycode == W_KEY)
	{
		env->cam->pos.z += 10;
		printf("W\n");
	}
	if (keycode == A_KEY)
	{
		printf("A\n");
		env->cam->pos.x -= 10;
	}
	if (keycode == D_KEY)
	{
		env->cam->pos.x += 10;
		printf("D\n");
	}
	if (keycode == S_KEY)
	{
		env->cam->pos.z -= 10;
		printf("S\n");
	}
	if (keycode == 65361)
	{
		env->cam->dir.x -= 1;
		printf("←\n");
	}
	if (keycode == 65363)
	{
		env->cam->dir.x += 1;
		printf("→\n");
	}
	if (keycode == 65362)
	{
		env->cam->dir.y += 1;
		printf("↑\n");
	}
	if (keycode == 65364)
	{
		env->cam->dir.y -= 1;
		printf("↓\n");
	}
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
	if (keycode == 65438)
	{
		env->lgt->pos.z -= 3;
		printf("0\n");
	}
	if (keycode == 65436)
	{
		env->lgt->pos.z += 3;
		printf("1\n");
	}
	trace_ray(env);
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	return (0);
}
void		graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y, "miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_handler, env);
	mlx_hook(env->win, DESTROYNOTIFY, 1, close_program, env);
	mlx_loop(env->mlx);
}
