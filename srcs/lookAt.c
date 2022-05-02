/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookAt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 13:27:11 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


/*
**	vector_direct : Takes the (x, y) pixel of our screen and transform it to
**		camera space.
*/

static t_vec		vector_direct(int fov, int resX, int resY, int x, int y)
{
	double		Px;
	double		Py;
	double		ratio;
	double		tang;

	tang = tan((fov * M_PI / 180) / 2);
	ratio = (double)resX / (double)resY;
	Px = (2 * ((x + 0.5) / resX) - 1) * ratio * tang;
	Py = (1 - 2 * ((y + 0.5) / resY)) * tang;
	return (v_init(Px, Py, -1, 0));
}

/*
**	canvas2view : Take the canvas point (x, y) and transform it to 3d world.
*/

t_ray			canvas2view(t_env *env, t_cam *cam, int x, int y)
{
	t_ray		ray;
	t_vec		new_pos;
	t_vec		new_dir;

	init_ray(&ray);
	ray.pos.w = 1;
	ray.dir = v_norm(vector_direct(cam->fov, env->res.x, env->res.y, x, y));
	new_pos = mat_mult_vec(cam->cam2world, ray.pos);
	new_pos = v_add(new_pos, cam->pos);
	new_dir = v_add(ray.pos, ray.dir);
	new_dir = mat_mult_vec(cam->cam2world, new_dir);
	new_dir = v_add(new_dir, cam->pos);
	ray.pos = new_pos;
	ray.dir = v_norm(v_sub(new_pos, new_dir));
	return (ray);
}
