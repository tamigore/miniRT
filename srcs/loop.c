/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/04/13 17:24:45 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define ROTA (15 * M_PI / 180)

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
	if (keycode == W_KEY)
	{
		env->cam->trans = translation_mat_init(vec_scale(10, env->cam->dir));
		// env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->trans);
		// printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("W\n");
	}
	if (keycode == A_KEY)
	{
		env->cam->trans = translation_mat_init(vec_scale(10, env->cam->right));
		// env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->trans);
		// printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("A\n");
	}
	if (keycode == D_KEY)
	{
		env->cam->trans = translation_mat_init(vec_scale(-10, env->cam->right));
		// env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->trans);
		// printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("D\n");
	}
	if (keycode == S_KEY)
	{
		env->cam->trans = translation_mat_init(vec_scale(-10, env->cam->dir));
		// env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->trans);
		// printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("S\n");
	}
	if (keycode == R_KEY)
	{
		env->cam->trans = translation_mat_init(vec_scale(10, env->cam->up));
		// env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->trans);
		// printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("R\n");
	}
	if (keycode == F_KEY)
	{
		env->cam->trans = translation_mat_init(vec_scale(-10, env->cam->up));
		// env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->trans);
		// printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("F\n");
	}
	if (keycode == 65364)
	{
		env->cam->rota = rotx_mat_init(-10);
		env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->rota);
		// printf("dir = (%.2f | %.2f | %.2f)\n", env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
		printf("←\n");
	}
	if (keycode == 65362)
	{
		env->cam->rota = rotx_mat_init(10);
		env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->rota);
		// printf("dir = (%.2f | %.2f | %.2f)\n", env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
		printf("→\n");
	}
	if (keycode == 65361)
	{
		env->cam->rota = roty_mat_init(10);
		env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->rota);
		// printf("dir = (%.2f | %.2f | %.2f)\n", env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
		printf("↑\n");
	}
	if (keycode == 65363)
	{
		env->cam->rota = roty_mat_init(-10);
		env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->rota);
		// printf("dir = (%.2f | %.2f | %.2f)\n", env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
		printf("↓\n");
	}
	if (keycode == 65438)
	{
		env->cam->rota = rotz_mat_init(10);
		env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->rota);
		// printf("dir = (%.2f | %.2f | %.2f)\n", env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
		printf("1\n");
	}
	if (keycode == 65436)
	{
		env->cam->rota = rotz_mat_init(-10);
		env->cam->cam2world = mat_mult_mat(env->cam->cam2world, env->cam->rota);
		// printf("dir = (%.2f | %.2f | %.2f)\n", env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
		printf("0\n");
	}
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
void		graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y, "miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_handler, env);
	mlx_hook(env->win, LEAVENOTIFY, 0, close_program, env);
	mlx_loop(env->mlx);
}
