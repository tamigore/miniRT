/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:29:06 by user42            #+#    #+#             */
/*   Updated: 2022/05/05 19:30:00 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define OBJ_MOVE 1

int	close_program(t_env *env)
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

/*	PRINT MATRIX
**	if (keycode == 112)
** 	{
** 		for (int i = 0; i < 4; i++)
** 		{
** 			for (int j = 0; j < 4; j++)
** 			{
** 				printf("|%.6f|", env->cam->cam2world.mat[i][j]);
** 			}
** 			printf("\n");
** 		}
** 		return (0);
** 	}
*/
int	key_handler(int keycode, t_env *env)
{
	printf("key code = %d\n", keycode);
	if (keycode == ESC_KEY)
		exit_sucess(env);
	if ((keycode >= 65361 && keycode <= 65438) || (keycode >= 32
			&& keycode <= 150))
		if (camera_move(keycode, env) == 0)
			return (0);
	if (keycode >= 65429 && keycode <= 65453)
		if (env->hit_obj)
			obj_move(keycode, env);
	trace_ray(env);
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_env *env)
{
	t_ray	ray;
	t_obj	*tmp;

	(void)button;
	tmp = env->obj;
	printf("click x : %d , y : %d\n", x, y);
	ray = canvas2view(env, env->cam, x, y);
	env->hit_obj = hit_objs(env->obj, &ray);
	if (env->hit_obj != NULL)
	{
		ray.hit = v_add(ray.pos, v_scale(ray.t - EPSILON, ray.dir));
		print_obj(env->hit_obj);
		printf("ray.hit : %f.x | %f.y | %f.z\n", ray.hit.x, ray.hit.y,
			ray.hit.z);
	}
	return (1);
}

void	graphic_loop(t_env *env)
{
	env->win = mlx_new_window(env->mlx, env->res.x, env->res.y, "miniRT");
	mlx_put_image_to_window(env->mlx, env->win, env->cam->img.ptr, 0, 0);
	mlx_mouse_hook(env->win, mouse_hook, env);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, key_handler, env);
	mlx_hook(env->win, 0, 17, close_program, env);
	mlx_loop(env->mlx);
}
