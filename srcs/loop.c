/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/04/06 18:36:19 by tamigore         ###   ########.fr       */
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
		double **trans = mat_init();
		trans[0] = mat_fil(1, 0, 0, env->cam->vz.x * 10);
		trans[1] = mat_fil(0, 1, 0, env->cam->vz.y * 10);
		trans[2] = mat_fil(0, 0, 1, env->cam->vz.z * 10);
		trans[3] = mat_fil(0, 0, 0, 1);
		env->cam->pos = vec3_x_mat4(env->cam->pos, trans);
		mat_free(trans);
		printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		// env->cam->pos.z += 10;
		printf("W\n");
	}
	if (keycode == A_KEY)
	{
		double **trans = mat_init();
		trans[0] = mat_fil(1, 0, 0, -env->cam->vy.x * 10);
		trans[1] = mat_fil(0, 1, 0, -env->cam->vy.y * 10);
		trans[2] = mat_fil(0, 0, 1, -env->cam->vy.z * 10);
		trans[3] = mat_fil(0, 0, 0, 1);
		env->cam->pos = vec3_x_mat4(env->cam->pos, trans);
		mat_free(trans);
		printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		printf("A\n");
		// env->cam->pos.x -= 10;
	}
	if (keycode == D_KEY)
	{
		double **trans = mat_init();
		trans[0] = mat_fil(1, 0, 0, env->cam->vy.x * 10);
		trans[1] = mat_fil(0, 1, 0, env->cam->vy.y * 10);
		trans[2] = mat_fil(0, 0, 1, env->cam->vy.z * 10);
		trans[3] = mat_fil(0, 0, 0, 1);
		env->cam->pos = vec3_x_mat4(env->cam->pos, trans);
		printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		mat_free(trans);
		// env->cam->pos.x += 10;
		printf("D\n");
	}
	if (keycode == S_KEY)
	{
		double **trans = mat_init();
		trans[0] = mat_fil(1, 0, 0, -env->cam->vz.x * 10);
		trans[1] = mat_fil(0, 1, 0, -env->cam->vz.y * 10);
		trans[2] = mat_fil(0, 0, 1, -env->cam->vz.z * 10);
		trans[3] = mat_fil(0, 0, 0, 1);
		env->cam->pos = vec3_x_mat4(env->cam->pos, trans);
		printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		mat_free(trans);
		// env->cam->pos.z -= 10;
		printf("S\n");
	}
	if (keycode == R_KEY)
	{
		double **trans = mat_init();
		trans[0] = mat_fil(1, 0, 0, env->cam->vy.x * 10);
		trans[1] = mat_fil(0, 1, 0, env->cam->vy.y * 10);
		trans[2] = mat_fil(0, 0, 1, env->cam->vy.z * 10);
		trans[3] = mat_fil(0, 0, 0, 1);
		env->cam->pos = vec3_x_mat4(env->cam->pos, trans);
		printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		mat_free(trans);
		// env->cam->pos.y += 10;
		printf("R\n");
	}
	if (keycode == F_KEY)
	{
		double **trans = mat_init();
		trans[0] = mat_fil(1, 0, 0, -env->cam->vy.x * 10);
		trans[1] = mat_fil(0, 1, 0, -env->cam->vy.y * 10);
		trans[2] = mat_fil(0, 0, 1, -env->cam->vy.z * 10);
		trans[3] = mat_fil(0, 0, 0, 1);
		env->cam->pos = vec3_x_mat4(env->cam->pos, trans);
		printf("pos = (%.2f | %.2f | %.2f)\n", env->cam->pos.x, env->cam->pos.y, env->cam->pos.z);
		mat_free(trans);
		// env->cam->pos.y -= 10;
		printf("F\n");
	}
	if (keycode == 65361)
	{
		double **rota = mat_init();
		rota[0] = mat_fil(cos(-ROTA), 0, sin(-ROTA), 0);
		rota[1] = mat_fil(0, 1, 0, 0);
		rota[2] = mat_fil(-sin(-ROTA), 0, cos(-ROTA), 0);
		rota[3] = mat_fil(0, 0, 0, 1);
		env->cam->dir = v_norm(vec3_x_mat4(env->cam->dir, rota));
		mat_free(rota);
		printf("←\n");
	}
	if (keycode == 65363)
	{
		double **rota = mat_init();
		rota[0] = mat_fil(cos(ROTA), 0, sin(ROTA), 0);
		rota[1] = mat_fil(0, 1, 0, 0);
		rota[2] = mat_fil(-sin(ROTA), 0, cos(ROTA), 0);
		rota[3] = mat_fil(0, 0, 0, 1);
		env->cam->dir = v_norm(vec3_x_mat4(env->cam->dir, rota));
		mat_free(rota);
		printf("→\n");
	}
	if (keycode == 65362)
	{
		double **rota = mat_init();
		rota[0] = mat_fil(1, 0, 0, 0);
		rota[1] = mat_fil(0, cos(-ROTA), -sin(-ROTA), 0);
		rota[2] = mat_fil(0, sin(-ROTA), cos(-ROTA), 0);
		rota[3] = mat_fil(0, 0, 0, 1);
		env->cam->dir = v_norm(vec3_x_mat4(env->cam->dir, rota));
		mat_free(rota);
		printf("↑\n");
	}
	if (keycode == 65364)
	{
		double **rota = mat_init();
		rota[0] = mat_fil(1, 0, 0, 0);
		rota[1] = mat_fil(0, cos(ROTA), -sin(ROTA), 0);
		rota[2] = mat_fil(0, sin(ROTA), cos(ROTA), 0);
		rota[3] = mat_fil(0, 0, 0, 1);
		env->cam->dir = v_norm(vec3_x_mat4(env->cam->dir, rota));
		mat_free(rota);
		printf("↓\n");
	}
	return (1);
}

int			key_handler(int keycode, t_env *env)
{
	printf("key code = %d\n", keycode);
	if (keycode == ESC_KEY)
		exit_sucess(env);
	if ((keycode >= 65361 && keycode <= 65364) || (keycode >= 32 && keycode <= 150))
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
	mlx_hook(env->win, LEAVENOTIFY, 0, close_program, env);
	mlx_loop(env->mlx);
}
