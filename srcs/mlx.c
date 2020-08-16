/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:33:11 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/11 18:05:02 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		mlx_creat_all(t_env **env)
{
	int	bpp;
	int	size_line;
	int	endian;

	bpp = 1;
	size_line = bpp * (*env)->res->x;
	endian = 0;
	if (!((*env)->mlx->ptr = mlx_init()))
		return (FAILURE);
	if (!((*env)->mlx->win = mlx_new_window((*env)->mlx->ptr, (*env)->res->x,
		(*env)->res->y, "MiniRT")))
		return (FAILURE);
	if (!((*env)->mlx->ima = mlx_new_image((*env)->mlx->ptr, (*env)->res->x,
		(*env)->res->y)))
		return (FAILURE);
	if (!((*env)->mlx->adr = mlx_get_data_addr((*env)->mlx->ima,
		&bpp, &size_line, &endian)))
		return (FAILURE);
	return(win_pixel(*env, 0, 0));
}

int		win_pixel(t_env *env, int x, int y)
{
	t_v3	cam;
	t_v3	cam2;

	while (y < env->res->y)
	{
		x = 0;
		while (x < env->res->x)
		{
		//	if (!(mlx_pixel_put(env->mlx->ptr, env->mlx->win, x, y,
		//		color(env, x, y))))
		//		return (FAILURE);
			cam = cam_pixel(env, x, y);
			x++;
		}
		y++;
	}
	cam2 = v_init(env->cam->vx, env->cam->vy, env->cam->vz);
	printf("%f/%f/%f // %f/%f/%f\n", cam.x, cam.y, cam.z, cam2.x, cam2.y, cam2.z);
	return (SUCCESS);
}

t_v3		cam_pixel(t_env *env, int x, int y)
{
	t_v3	vec;
	double	ratio;
	double	Px;
	double	Py;

	ratio = env->res->x / env->res->y;
	Px = (2 * ((x + 0.5) / env->res->x) - 1) * ratio *
		sin(rad(env->cam->fov)/2) / cos(rad(env->cam->fov)/2);
	Py = (1 - (2 * (y + 0.5) / env->res->y)) * sin(rad(env->cam->fov)/2) /
		cos(rad(env->cam->fov)/2);
	vec.x = Px;
	vec.y = Py;
	vec.z = -1;
	return (vec);
}

