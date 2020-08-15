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
	while (y < env->res->y)
	{
		x = 0;
		while (x < env->res->x)
		{
			if (!(mlx_pixel_put(env->mlx->ptr, env->mlx->win, x, y,
				color(env, x, y))))
				return (FAILURE);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int		color(t_env *env, int x, int y)
{
	float	NDCx;
	float	NDCy;
	float	Sx;
	float	Sy;
	float	ratio;
	float	Camx;
	float	Camy;

	NDCx = (x + 0.5) / env->res->x;
	NDCy = (y + 0.5) / env->res->y;
	Sx = 2 * NDCx - 1;
	Sy = 1 - 2 * NDCy;
	ratio = env->res->x / env->res->y;
	Camx = (2 * Sx - 1) * ratio;
	Camy = 1 - 2 * Sy;
	return (250);
}
