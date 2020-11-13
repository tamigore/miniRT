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

int			mlx_creat_all(t_env **env)
{
	int	bpp;
	int	size_line;
	int	endian;

	bpp = 1;
	size_line = bpp * (*env)->res->x;
	endian = 0;
	if (!((*env)->mlx->ptr = mlx_init()))
		return (FAILURE);
	if (!((*env)->mlx->win = mlx_new_window((*env)->mlx->ptr,
		(*env)->res->x, (*env)->res->y, "MiniRT")))
		return (FAILURE);
	if (!((*env)->mlx->ima = mlx_new_image((*env)->mlx->ptr,
		(*env)->res->x, (*env)->res->y)))
		return (FAILURE);
	if (!((*env)->mlx->adr = mlx_get_data_addr((*env)->mlx->ima,
		&bpp, &size_line, &endian)))
		return (FAILURE);
	return(win_pixel(*env));
}

int			win_pixel(t_env *env)
{
	int		color;
	double	x;
	double	y;
	t_v3	D;

	x = 0;
	y = 0;
	env->ray->ori = v_init(env->cam->ori.x,env->cam->ori.y, env->cam->ori.z);
	printf("begin!\n");
	while (y < env->res->y)
	{
		x = 0;
		while (x < env->res->x)
		{
			D = canvas2view(env, x, y);
			ft_ray(env->ray, env->ray->ori, D, 0);
			color = trace_ray(env, env->ray);
			mlx_pixel_put(env->mlx->ptr, env->mlx->win, x++, y, color);
		}
		y++;
	}
	return (1);
}

t_v3		canvas2view(t_env *env, int x, int y)
{
	t_v3	vec;
	t_v3	cam;
	t_v3	pos;

	vec = vector_direct(env->cam->fov, env->res->x, env->res->y, x, y);
	pos = v_init(env->cam->ori.x, env->cam->ori.y, env->cam->ori.z);
	cam = v_init(env->cam->dir.x, env->cam->dir.y, env->cam->dir.z);
	env->cam->mat = lookAt(env->cam->mat, cam, vec, pos);
	vec = vec3Xmat4(vec, env->cam->mat);
	vec = v_norm(vec);
	return (vec);
}

t_v3		vector_direct(int fov, int resX, int resY, int x, int y)
{
	double	Px;
	double	Py;
	double	ratio;
	double	tang;

	tang = tan(rad(fov) / 2);
	if (resX >= resY)
		ratio = resX / resY;
	else
		ratio = resY / resX;
	Px = (2 * ((x + 0.5) / resX) - 1) * (1 / ratio) * tang;
	Py = (1 - 2 * ((y + 0.5) / resY)) * tang;
	return (v_init(Px, Py, -1));
}
