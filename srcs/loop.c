/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tamigore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 11:47:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

int			next_cam(int keycode, t_env *env)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode != SP_KEY)
		return (0);
	env->img = env->img->next;
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
	return (1);
}

void		graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y,
															"miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
	mlx_hook(env->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_program, 0);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, next_cam, env);
	mlx_loop(env->mlx);
}
