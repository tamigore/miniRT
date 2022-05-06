/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:29:01 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:12:15 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_left_right(t_env *env, int keycode)
{
	if (keycode == A_KEY)
	{
		env->cam->trans = translation_mat_init(v_init(10, 0, 0, 0));
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->trans);
		printf("A\n");
	}
	else if (keycode == D_KEY)
	{
		env->cam->trans = translation_mat_init(v_init(-10, 0, 0, 0));
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->trans);
		printf("D\n");
	}
}

void	move_forward_backward(t_env *env, int keycode)
{
	if (keycode == W_KEY)
	{
		env->cam->trans = translation_mat_init(v_init(0, 0, 10, 0));
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->trans);
		printf("W\n");
	}
	else if (keycode == S_KEY)
	{
		env->cam->trans = translation_mat_init(v_init(0, 0, -10, 0));
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->trans);
		printf("S\n");
	}
}

void	move_up_down(t_env *env, int keycode)
{
	if (keycode == R_KEY)
	{
		env->cam->trans = translation_mat_init(v_init(0, -10, 0, 0));
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->trans);
		printf("R\n");
	}
	else if (keycode == F_KEY)
	{
		env->cam->trans = translation_mat_init(v_init(0, 10, 0, 0));
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->trans);
		printf("F\n");
	}
}

void	rotate_1(t_env *env, int keycode)
{
	if (keycode == DOWN_KEY)
	{
		env->cam->rota = rotx_mat_init(-10);
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->rota);
		printf("↓\n");
	}
	else if (keycode == UP_KEY)
	{
		env->cam->rota = rotx_mat_init(10);
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->rota);
		printf("↑\n");
	}
	else if (keycode == LEFT_KEY)
	{
		env->cam->rota = roty_mat_init(10);
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->rota);
		printf("←\n");
	}
}

void	rotate_2(t_env *env, int keycode)
{
	if (keycode == RIGHT_KEY)
	{
		env->cam->rota = roty_mat_init(-10);
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->rota);
		printf("→\n");
	}
	else if (keycode == 65438)
	{
		env->cam->rota = rotz_mat_init(10);
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->rota);
		printf("0\n");
	}
	else if (keycode == 65436)
	{
		env->cam->rota = rotz_mat_init(-10);
		env->cam->c2w = mat_mult_mat(env->cam->c2w, env->cam->rota);
		printf("1\n");
	}
}
