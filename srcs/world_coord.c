/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:30:44 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 19:17:34 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		set_mat_cam(t_cam *cam, t_vec rotation)
{
	(void)rotation;
	t_mat	mat;

	mat = world2obj_mat(cam->dir, cam->up, cam->right);
	// mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(1, 0, 0, 0), rotation.x));
	// mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 1, 0, 0), rotation.y));
	// mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 0, 1, 0), rotation.z));
	cam->world2cam = mat;
	cam->cam2world = obj2world_mat(cam->world2cam);
}

void		set_mat_obj(t_obj *obj, t_vec rotation)
{
	t_mat	mat;

	mat = world2obj_mat(obj->dir, obj->up, obj->right);
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(1, 0, 0, 0), rotation.x));
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 1, 0, 0), rotation.y));
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 0, 1, 0), rotation.z));
	obj->world2obj = mat;
	obj->obj2world = obj2world_mat(obj->world2obj);
}

t_mat		world2obj_mat(t_vec dir, t_vec up, t_vec right)
{
	t_mat	mat;
	t_vec	zaxis;
	t_vec	yaxis;
	t_vec	xaxis;

	zaxis = dir;
	xaxis = right;
	yaxis = up;
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

t_mat		obj2world_mat(t_mat world2cam)
{
	t_mat	mat;

	mat = world2cam;
	mat.mat[0][1] = world2cam.mat[1][0];
	mat.mat[0][2] = world2cam.mat[2][0];
	mat.mat[0][3] = world2cam.mat[3][0];
	mat.mat[1][0] = world2cam.mat[0][1];
	mat.mat[1][2] = world2cam.mat[2][1];
	mat.mat[1][3] = world2cam.mat[3][1];
	mat.mat[2][0] = world2cam.mat[0][2];
	mat.mat[2][1] = world2cam.mat[1][2];
	mat.mat[2][3] = world2cam.mat[3][2];
	mat.mat[3][0] = world2cam.mat[0][3];
	mat.mat[3][1] = world2cam.mat[1][3];
	mat.mat[3][2] = world2cam.mat[2][3];
	return (mat);
}

t_vec		get_orthogonal(t_vec vec)
{
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;
	t_vec	v4;
	t_vec	v5;
	t_vec	v6;

	v1 = v_cross(v_init(1, 0, 0, 0), vec);
	v2 = v_cross(v_init(0, 1, 0, 0), vec);
	v3 = v_cross(v_init(0, 0, 1, 0), vec);
	v4 = v_cross(v_init(-1, 0, 0, 0), vec);
	v5 = v_cross(v_init(0, -1, 0, 0), vec);
	v6 = v_cross(v_init(0, 0, -1, 0), vec);
	if (v_dot(v1, vec) == 0 && v_dot(v1, vec) != 1)
		return (v1);
	else if (v_dot(v3, vec) == 0 && v_dot(v3, vec) != 1)
		return (v3);
	else if (v_dot(v4, vec) == 0 && v_dot(v4, vec) != 1)
		return (v4);
	else if (v_dot(v5, vec) == 0 && v_dot(v5, vec) != 1)
		return (v5);
	else if (v_dot(v6, vec) == 0 && v_dot(v6, vec) != 1)
		return (v6);
	else
		return (v2);
}
