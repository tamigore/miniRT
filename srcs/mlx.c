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

int	mlx_creat_all(t_env **env)
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

int	win_pixel(t_env *env, int x, int y)
{
	t_v3	O;
	t_v3	D;
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	O = v_init(env->cam->x,env->cam->y, env->cam->z);
	while (x < env->res->x)
	{
		while (y < env->res->y)
		{
			D = canvas2view(x, y)
			color = trace_ray(O, D)
			mls_pixelput(env->mlx->ptr, env->mlx->win, x, y, color);
		}
	}
}

t_v3	canvas2view(x, y)

int	trace_ray(t_v3 O, t_v3 D)
{
	
}

int	color_sph(t_env *env, t_v3 O, t_v3 D)
{
	t_v3	C;
	t_v3	OC;
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	t;

	C = v_init(env->sph->x, env->sph->y, env->sph->z);
	OC = v_sub(D, O);
	a = v_dot(D, D);
	b = 2 * v_dot(OC, D);
	c = v_dot(OC, OC) - (env->sph->d / 2) * (env->sph->d / 2);
	t1 = (-b + sqrt(b*b - 4 * a * c)) / (2 * a);
	t2 = (-b - sqrt(b*b - 4 * a * c)) / (2 * a);
	if (t1 > 1 && t1 <= t2)
		return (rgb2color(env->sph->R, env->sph->G, env->sph->B));
	else if (t2 > 1 && t2 <= t1)
		return (rgb2color(env->sph->R, env->sph->G, env->sph->B));
	else
		return (color(NULL))
}
