/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:26:22 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/03 15:11:42 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		get_resolution(t_env *env)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (*(env->sceen) == 'R')
		(env->sceen)++;
	if (env->res.check == 1)
		exit_error(env, RES_DUP);
	env->res.check = 1;
	env->res.x = str_to_unsigned(env);
	env->res.y = str_to_unsigned(env);
	mlx_get_screen_size(env->mlx, &x, &y);
	if (env->res.x > x)
		env->res.x = x;
	if (env->res.y > y)
		env->res.y = y;
	if (env->res.y < 300 || env->res.x < 300)
		exit_error(env, RES_LOW);
}

void		get_ambient(t_env *env)
{
	if (*(env->sceen) == 'A')
		(env->sceen)++;
	if (env->amb.check == 1)
		exit_error(env, AMB_DUP);
	env->amb.check = 1;
	env->amb.ratio = str_to_double(env);
	env->amb.color.x = str_to_unsigned(env);
	env->amb.color.y = str_to_unsigned(env);
	env->amb.color.z = str_to_unsigned(env);
	if (!check_val(env->amb.ratio, 0, 1) || !check_val(env->amb.color.z, 0, 255)
		|| !check_val(env->amb.color.y, 0, 255)
		|| !check_val(env->amb.color.x, 0, 255))
		exit_error(env, LIGHT_FMT);
}

void		get_camera(t_env *env)
{
	t_cam	*cam;

	printf("%s\n",env->sceen);	
	if (*(env->sceen) == 'c' || *(env->sceen) == 'C')
		(env->sceen)++;
	cam = init_camera(env);
	cam->pos.x = str_to_double(env);
	cam->pos.y = str_to_double(env);
	cam->pos.z = str_to_double(env);
	cam->dir.x = str_to_double(env);
	cam->dir.y = str_to_double(env);
	cam->dir.z = str_to_double(env);
	cam->dir = v_norm(cam->dir);
	cam->fov = str_to_unsigned(env);
	if (!check_val(cam->fov, 0, 180) || !check_vec(cam->dir)
		|| fabs(cam->pos.x) == INFINITY || fabs(cam->pos.y) == INFINITY
		|| fabs(cam->pos.z) == INFINITY)
		exit_error(env, CAM_FMT);
	cam->dir = v_norm(cam->dir);
	cam->up = v_norm(get_orthogonal(cam->dir));
	cam->right = v_norm(v_cross(cam->dir, cam->up));
	set_mat_cam(cam, v_init(0,0,0,0));
	env->nb_cam++;
	append_cam(&(env->cam), cam);
}

void		get_light(t_env *env)
{
	t_lgt	*lgt;

	if (*(env->sceen) == 'l' || *(env->sceen) == 'L')
		(env->sceen)++;
	lgt = init_light(env);
	lgt->pos.x = str_to_double(env);
	lgt->pos.y = str_to_double(env);
	lgt->pos.z = str_to_double(env);
	lgt->ratio = str_to_double(env);
	lgt->color.x = str_to_unsigned(env);
	lgt->color.y = str_to_unsigned(env);
	lgt->color.z = str_to_unsigned(env);
	if (!check_val(lgt->ratio, 0, 1) || !check_val(lgt->color.z, 0, 255)
		|| !check_val(lgt->color.y, 0, 255) || !check_val(lgt->color.x, 0, 255)
		|| fabs(lgt->pos.x) == INFINITY || fabs(lgt->pos.y) == INFINITY
		|| fabs(lgt->pos.z) == INFINITY)
		exit_error(env, LIGHT_FMT);
	env->nb_lgt++;
	append_lgt(&(env->lgt), lgt);
}
