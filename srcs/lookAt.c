/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookAt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/13 16:15:58 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static t_vec		look_at(t_vec dir, t_vec cam_dir)
// {
// 	t_vec		x;
// 	t_vec		y;
// 	t_vec		z;
// 	t_vec		res;

// 	z = cam_dir;
// 	if (cam_dir.y == 1 || cam_dir.y == -1)
// 		x = cam_dir.y == 1 ? vec_init(1, 0, 0, 0) : vec_init(-1, 0, 0, 0);
// 	else
// 		x = vec_cross(vec_init(0, 1, 0, 0), z);
// 	y = vec_cross(z, x);
// 	res.x = dir.x * x.x + dir.y * y.x + dir.z * z.x;
// 	res.y = dir.x * x.y + dir.y * y.y + dir.z * z.y;
// 	res.z = dir.x * x.z + dir.y * y.z + dir.z * z.z;
// 	return (res);
// }

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
	return (vec_init(Px, Py, -1, 0));
}

// static t_vec		vector_direct(int fov, int resX, int resY, int x, int y)
// {
// 	double		Px;
// 	double		Py;
// 	double		Pz;
// 	double		ratio;
// 	double		tang;

// 	tang = tan((fov * M_PI / 180) / 2);
// 	ratio = (double)resX / (double)resY;
// 	Px = ((x + 0.5) - (resX / 2)) * ratio * tang;
// 	Py = - ((y + 0.5) - (resY / 2)) * tang;
// 	Pz = -(resY / (2 * tang));
// 	return (vec_init(Px, Py, Pz, 0));
// }

/*
**	canvas2view : Take the canvas point (x, y) and transform it to 3d world.
*/

t_ray			canvas2view(t_env *env, t_cam *cam, int x, int y)
{
	t_ray		ray;
	t_vec		new_pos;
	t_vec		new_dir;

	init_ray(&ray);
	ray.dir = vec_norm(vector_direct(cam->fov, env->res.x, env->res.y, x, y));
	new_pos = mat_mult_vec(cam->cam2world, ray.pos);
	new_pos = vec_add(ray.pos, cam->pos);
	new_dir = vec_add(ray.pos, ray.dir);
	new_dir = mat_mult_vec(cam->cam2world, new_dir);
	new_dir = vec_add(new_dir, cam->pos);
	ray.pos = new_pos;
	ray.dir = vec_norm(vec_sub(new_pos, new_dir));
	// vec = vec_norm(look_at(vec, vec_norm(cam->dir)));
	return (ray);
}
