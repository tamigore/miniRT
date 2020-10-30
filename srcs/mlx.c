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
	return(win_pixel(*env, 0, 0));
}

int			win_pixel(t_env *env, int x, int y)
{
	t_v3	O;
	t_v3	D;
	int		color;

	O = v_init(env->cam->x,env->cam->y, env->cam->z);
	while (y < env->res->y)
	{
		x = 0;
		while (x < env->res->x)
		{
			D = canvas2view(env, x, y);
			color = trace_ray(env, O, D);
			mlx_pixel_put(env->mlx->ptr, env->mlx->win, x++, y, color);
		}
		y++;
	}
	printf("Victory !\n");
	return (1);
}

t_v3		canvas2view(t_env *env, int x, int y)
{
	t_v3	vec;
	t_v3	cam;
	t_v3	pos;

	vec = vector_direct(env->cam->fov, env->res->x, env->res->y, x, y);
	pos = v_init(env->cam->x, env->cam->y, env->cam->z);
	cam = v_init(env->cam->vx, env->cam->vy, env->cam->vz);
	env->cam->mat = lookAt(env->cam->mat, cam, vec, pos);
	vec = vecXmat(vec, env->cam->mat);
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

int			trace_ray(t_env *env, t_v3 orig, t_v3 dir)
{
	int		hitColor;
	t_env	*hitObject;
	double	dist;
	t_v3	Phit;
	t_v3	Nhit;
	double	tex[2];
	double	pattern;
	double	scale;

	hitColor = 0;
	hitObject = NULL;
	if (trace(env, orig, dir, &dist, hitObject))
	{
		Phit = v_add(orig, v_multi(dist, dir));
        Nhit = v_sub(Phit, v_init(env->sph->x, env->sph->y, env->sph->z));
        Nhit = v_norm(Nhit);
		tex[0] = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5;
		tex[1] = acos(Nhit.y) / M_PI;
		pattern = ((tex[0] * 4 > 0.5) ^ (tex[1] * 4 > 0.5));
		if ((hitColor = MaxVal(4 ,0, v_dot(Nhit, v_sub(v_init(0, 0, 0), dir)) *				hitObject->color, hitObject->color * 0.8, pattern)) == NAN)
			return (0);
	}
	return hitColor;
}
