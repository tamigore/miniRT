/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:30:44 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 18:51:39 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		set_mat_cam(t_cam *cam, t_vec rotation)
{
	t_mat	mat;

	mat = world2cam_mat(cam);
	mat = mat_mult_mat(mat, rotmat_axis_angle(vec_init(1, 0, 0, 0), rotation.x));
	mat = mat_mult_mat(mat, rotmat_axis_angle(vec_init(0, 1, 0, 0), rotation.y));
	mat = mat_mult_mat(mat, rotmat_axis_angle(vec_init(0, 0, 1, 0), rotation.z));
	cam->world2cam = mat;
	cam->cam2world = cam2world_mat(cam);
}

t_mat		world2cam_mat(t_cam *cam)
{
	t_mat	mat;
	t_vec	zaxis;
	t_vec	yaxis;
	t_vec	xaxis;

	zaxis = cam->dir;
	xaxis = cam->right;
	yaxis = cam->up;
	mat = identity_mat_init();
	mat.mat[0][0] = xaxis.x;
	mat.mat[0][1] = xaxis.y;
	mat.mat[0][2] = xaxis.z;
	mat.mat[1][0] = yaxis.x;
	mat.mat[1][1] = yaxis.y;
	mat.mat[1][2] = yaxis.z;
	mat.mat[2][0] = zaxis.x;
	mat.mat[2][1] = zaxis.y;
	mat.mat[2][2] = zaxis.z;
	return (mat);
}

t_mat		cam2world_mat(t_cam *cam)
{
	t_mat	mat;

	mat = cam->world2cam;
	mat.mat[0][1] = cam->world2cam.mat[1][0];
	mat.mat[0][2] = cam->world2cam.mat[2][0];
	mat.mat[0][3] = cam->world2cam.mat[3][0];
	mat.mat[1][0] = cam->world2cam.mat[0][1];
	mat.mat[1][2] = cam->world2cam.mat[2][1];
	mat.mat[1][3] = cam->world2cam.mat[3][1];
	mat.mat[2][0] = cam->world2cam.mat[0][2];
	mat.mat[2][1] = cam->world2cam.mat[1][2];
	mat.mat[2][3] = cam->world2cam.mat[3][2];
	mat.mat[3][0] = cam->world2cam.mat[0][3];
	mat.mat[3][1] = cam->world2cam.mat[1][3];
	mat.mat[3][2] = cam->world2cam.mat[2][3];
	return (mat);
}

t_vec	get_orthogonal(t_vec vec)
{
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;

	v1 = vec_cross(vec_init(1, 0, 0, 0), vec);
	v2 = vec_cross(vec_init(0, 1, 0, 0), vec);
	v3 = vec_cross(vec_init(0, 0, 1, 0), vec);
	if (vec_dot(v1, vec) == 0)
		return (v1);
	else if (vec_dot(v2, vec) == 0)
		return (v2);
	else if (vec_dot(v3, vec) == 0)
		return (v3);
	return (vec_init(0, 0, 0, 0));
}
