/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookAt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:11:18 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	vector_direct : Takes the (x, y) pixel of our screen and transform it to
**		camera space.
*/
static t_vec	vector_direct(t_env *env, int x, int y)
{
	double	px;
	double	py;
	double	ratio;
	double	tang;

	tang = tan((env->cam->fov * M_PI / 180) / 2);
	ratio = (double)env->res.x / (double)env->res.y;
	px = (2 * ((x + 0.5) / env->res.x) - 1) * ratio * tang;
	py = (1 - 2 * ((y + 0.5) / env->res.y)) * tang;
	return (v_init(px, py, -1, 0));
}

/*
**	canvas2view : Take the canvas point (x, y) and transform it to 3d world.
*/
t_ray	canvas2view(t_env *env, t_cam *cam, int x, int y)
{
	t_ray	ray;
	t_vec	new_pos;
	t_vec	new_dir;

	init_ray(&ray);
	ray.pos.w = 1;
	ray.dir = v_norm(vector_direct(env, x, y));
	new_pos = mat_mult_vec(cam->c2w, ray.pos);
	new_pos = v_add(new_pos, cam->pos);
	new_dir = v_add(ray.pos, ray.dir);
	new_dir = mat_mult_vec(cam->c2w, new_dir);
	new_dir = v_add(new_dir, cam->pos);
	ray.pos = new_pos;
	ray.dir = v_norm(v_sub(new_pos, new_dir));
	return (ray);
}
