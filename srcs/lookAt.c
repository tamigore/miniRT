/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookAt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/06 17:29:46 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_v3		look_at(t_v3 dir, t_v3 cam_dir)
{
	t_v3		x;
	t_v3		y;
	t_v3		z;
	t_v3		res;

	z = cam_dir;
	if (cam_dir.y == 1 || cam_dir.y == -1)
		x = cam_dir.y == 1 ? v_init(1, 0, 0) : v_init(-1, 0, 0);
	else
		x = v_cross(v_init(0, 1, 0), z);
	y = v_cross(z, x);
	res.x = dir.x * x.x + dir.y * y.x + dir.z * z.x;
	res.y = dir.x * x.y + dir.y * y.y + dir.z * z.y;
	res.z = dir.x * x.z + dir.y * y.z + dir.z * z.z;
	return (res);
}

/*
**	vector_direct : Takes the (x, y) pixel of our screen and transform it to
**		camera space.
*/

static t_v3		vector_direct(int fov, int resX, int resY, int x, int y)
{
	double		Px;
	double		Py;
	double		ratio;
	double		tang;

	tang = tan((fov * M_PI / 180) / 2);
	ratio = (double)resX / (double)resY;
	Px = (2 * ((x + 0.5) / resX) - 1) * ratio * tang;
	Py = (1 - 2 * ((y + 0.5) / resY)) * tang;
	return (v_init(Px, Py, 1));
}

// static t_v3		vector_direct(int fov, int resX, int resY, int x, int y)
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
// 	Pz = (resY / (2 * tang));
// 	return (v_init(Px, Py, Pz));
// }

/*
**	canvas2view : Take the canvas point (x, y) and transform it to 3d world.
*/

t_v3			canvas2view(t_env *env, t_cam *cam, int x, int y)
{
	t_v3		vec;

	vec = vector_direct(cam->fov, env->res.x, env->res.y, x, y);
	vec = v_norm(vec);
	vec = look_at(vec, v_norm(cam->dir));
	vec = v_norm(vec);
	return (vec);
}

/*
double	**lookAt(double **cam2world, t_v3 dir, t_v3 pos)
{
	t_v3	X;
	t_v3	Y;
	t_v3	Z;
	double	**mat;
	double	**tmp;
	double	**inv;

	Z = v_norm(v_sub(dir, pos));
	if (v_comp(X = v_cross(v_init(0, 1, 0), Z), v_init(0, 0, 0)))
		X = v_cross(v_init(1, 0, 0), Z);
	Y = v_cross(Z, X);
	if (!(tmp = mat_init()))
		return (NULL);
	tmp[0] = mat_fil(X.x, X.y, X.z, pos.x);
	tmp[1] = mat_fil(Y.x, Y.y, Y.z, pos.y);
	tmp[2] = mat_fil(Z.x, Z.z, Z.z, pos.z);
	tmp[3] = mat_fil(0, 0, 0, 1);
	if (!(mat = mat_init()))
		return (NULL);
	mat[0] = mat_fil(1, 0, 0, -pos.x);
	mat[1] = mat_fil(0, 1, 0, -pos.y);
	mat[2] = mat_fil(0, 0, 1, -pos.z);
	mat[3][3] = 1;
	if (!(inv = mat_init()))
		return (NULL);
	mat4_x_mat4(tmp, mat, inv);
	mat_free(mat);
	mat_free(tmp);
	if (!(mat_invers(inv, cam2world)))
	{
		cam2world = inv;
		free(inv);
		return (cam2world);
	}
	mat_free(inv);
	return (cam2world);
}
*/
