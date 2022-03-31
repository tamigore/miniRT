/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanter <dasanter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/03/29 14:28:41 by dasanter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			close_program(t_env *env)
{
	exit_sucess(env);
	return (0);
}

int			key_handler(int keycode, t_env *env)
{
	printf("key code = %d\n", keycode);
	if (keycode == ESC_KEY)
		exit_sucess(env);
	/*if (keycode == SP_KEY)
	{
		printf("next image\n");
		printf("old img addr : %p\n", &env->img);
		env->img = env->img->next;
		printf("new img addr : %p\n", &env->img);
		mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
		return (0);
	}*/
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
	if (keycode == 113)
	{
		env->cam->dir.x -= 0.01;
		printf("Q\n");
	}
	if (keycode == 101)
	{
		env->cam->dir.x += 0.01;
		printf("E\n");
	}
	if (keycode == 65363)
	{
		env->lgt->pos.x += 3;
		printf("E\n");
	}
	if (keycode == 65361)
	{
		env->lgt->pos.x -= 3;
		printf("E\n");
	}
	if (keycode == 65362)
	{
		env->lgt->pos.y += 3;
		printf("E\n");
	}
	if (keycode == 65438)
	{
		env->lgt->pos.z -= 3;
		printf("E\n");
	}
	if (keycode == 65436)
	{
		env->lgt->pos.z += 3;
		printf("E\n");
	}
	if (keycode == 65364)
	{
		env->lgt->pos.y -= 3;
		printf("E\n");
	}
	render(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
	return (0);
}
void		graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y, "miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
	mlx_hook(env->win, 0, DESTROYNOTIFY, close_program, env);
	// mlx_hook(env->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_program, env);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_handler, env);
	mlx_loop(env->mlx);
}
