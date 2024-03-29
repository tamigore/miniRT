/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:30:44 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:11:42 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_mat_cam(t_cam *cam, t_vec rotation)
{
	t_mat	mat;

	mat = world2obj_mat(cam->dir, cam->up, cam->right);
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(1, 0, 0, 0), rotation.x));
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 1, 0, 0), rotation.y));
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 0, 1, 0), rotation.z));
	cam->w2c = mat;
	cam->c2w = obj2world_mat(cam->w2c);
}

void	set_mat_obj(t_obj *obj, t_vec rotation)
{
	t_mat	mat;

	mat = world2obj_mat(obj->dir, obj->up, obj->right);
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(1, 0, 0, 0), rotation.x));
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 1, 0, 0), rotation.y));
	mat = mat_mult_mat(mat, rotmat_axis_angle(v_init(0, 0, 1, 0), rotation.z));
	obj->world2obj = mat;
	obj->obj2world = obj2world_mat(obj->world2obj);
}

t_mat	world2obj_mat(t_vec dir, t_vec up, t_vec right)
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

t_mat	obj2world_mat(t_mat w2c)
{
	t_mat	mat;

	mat = w2c;
	mat.mat[0][1] = w2c.mat[1][0];
	mat.mat[0][2] = w2c.mat[2][0];
	mat.mat[0][3] = w2c.mat[3][0];
	mat.mat[1][0] = w2c.mat[0][1];
	mat.mat[1][2] = w2c.mat[2][1];
	mat.mat[1][3] = w2c.mat[3][1];
	mat.mat[2][0] = w2c.mat[0][2];
	mat.mat[2][1] = w2c.mat[1][2];
	mat.mat[2][3] = w2c.mat[3][2];
	mat.mat[3][0] = w2c.mat[0][3];
	mat.mat[3][1] = w2c.mat[1][3];
	mat.mat[3][2] = w2c.mat[2][3];
	return (mat);
}

t_vec	get_orthogonal(t_vec vec)
{
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;
	t_vec	ret;

	v1 = v_cross(v_init(1, 0, 0, 0), vec);
	v2 = v_cross(v_init(0, 1, 0, 0), vec);
	v3 = v_cross(v_init(0, 0, 1, 0), vec);
	ret = v2;
	if (v_dot(v1, vec) <= 0.1 && v_dot(v1, vec) >= -0.1)
		ret = v1;
	else if (v_dot(v3, vec) <= 0.1 && v_dot(v3, vec) >= -0.1)
		ret = v3;
	if (v_comp(v_cross(ret, vec), v_init(0, 0, 0, 0))
		|| v_comp(v_cross(ret, vec), v_init(NAN, NAN, NAN, 0)))
	{
		if (v_comp(ret, v2))
			ret = v1;
		else
			ret = v2;
	}
	return (ret);
}
