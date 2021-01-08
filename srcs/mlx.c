/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:33:11 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/07 18:45:49 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			mlx_creat_all(t_env *env)
{
	int		bpp;
	int		size_line;
	int		endian;

	bpp = 1;
	size_line = bpp * env->res->x;
	endian = 0;
	if (!(env->mlx->ptr = mlx_init()))
		return (FAIL);
	if (!(env->mlx->win = mlx_new_window(env->mlx->ptr,
		env->res->x, env->res->y, "MiniRT")))
		return (FAIL);
	if (!(env->mlx->ima = mlx_new_image(env->mlx->ptr,
		env->res->x, env->res->y)))
		return (FAIL);
	if (!(env->mlx->adr = mlx_get_data_addr(env->mlx->ima,
		&bpp, &size_line, &endian)))
		return (FAIL);
	return(win_pixel(env));
}

int			win_pixel(t_env *env)
{
	int		color;
	double	x;
	double	y;

	x = 0;
	y = 0;
	env->ray->pos = env->cam->pos;
	while (y < env->res->y)
	{
		x = 0;
		while (x < env->res->x)
		{
			if (v_comp((env->ray->dir = canvas2view(env, x, y)), v_init(0,0,0)))
				return (-1);
			color = trace_ray(env);
			mlx_pixel_put(env->mlx->ptr, env->mlx->win, x++, y, color);
			x++;
		}
		y++;
	}
	return (1);
}

/*
**	canvas2view permet de passer des coordonées pixels au coordonées world 3d
*/

t_v3		canvas2view(t_env *env, int x, int y)
{
	t_v3	vec;

	vec = vector_direct(env->cam->fov, env->res->x, env->res->y, x, y);
	if (!(env->cam->mat = lookAt(env->cam->mat, env->cam->dir, env->cam->pos)))
	return (v_init(0, 0, 0));
	vec = vec3_x_mat4(vec, env->cam->mat);
	vec = v_norm(vec);
	return (vec);
/*
	t_v3	right;
	t_v3	up;
	t_v3	pos;

	right = v_init(1, 0, 0);
	up = v_cross(right, env->cam->dir);
	if (v_comp(up, v_init(0, 0, 0)))
	{
		right = v_init(0, 1, 0);
		up = v_cross(right, env->cam->dir);
	}
	pos = vector_direct(env->cam->fov, env->res->x, env->res->y, x, y);
	right = v_multi(pos.x, right);
	up = v_multi(pos.y, up);
	env->ray->ori = env->cam->ori;
	return (v_add(v_add(right, up), env->cam->dir));
*/
}

/*
**	vector_direct permet d'avoir les coordonées de l'éspace caméra
*/

t_v3		vector_direct(int fov, int resX, int resY, int x, int y)
{
	double	Px;
	double	Py;
	double	ratio;
	double	tang;

	tang = tan(rad(fov) / 2);
	ratio = resX / resY;
	Px = (2 * ((x + 0.5) / resX) - 1) * ratio * tang;
	Py = (1 - 2 * ((y + 0.5) / resY)) * tang;
	return (v_init(Px, Py, 1));
}
