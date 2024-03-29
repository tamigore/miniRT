/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_tr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:39:37 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 16:39:51 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat	mat_angle(t_vec axis, double cos, double sin, double t)
{
	t_mat		mat;
	double		tmp1;
	double		tmp2;

	mat = identity_mat_init();
	mat.mat[0][0] = cos + axis.x * axis.x * t;
	mat.mat[1][1] = cos + axis.y * axis.y * t;
	mat.mat[2][2] = cos + axis.z * axis.z * t;
	tmp1 = axis.x * axis.y * t;
	tmp2 = axis.z * sin;
	mat.mat[1][0] = tmp1 + tmp2;
	mat.mat[0][1] = tmp1 - tmp2;
	tmp1 = axis.x * axis.z * t;
	tmp2 = axis.y * sin;
	mat.mat[2][0] = tmp1 - tmp2;
	mat.mat[0][2] = tmp1 + tmp2;
	tmp1 = axis.y * axis.z * t;
	tmp2 = axis.x * sin;
	mat.mat[2][1] = tmp1 + tmp2;
	mat.mat[1][2] = tmp1 - tmp2;
	return (mat);
}

t_mat	rotmat_axis_angle(t_vec axis, double angle)
{
	double	cos;
	double	sin;
	double	t;
	t_mat	mat;

	if (angle == 0 || angle == NAN || v_len(axis) == 0)
		return (identity_mat_init());
	cos = cosf(angle);
	sin = sinf(angle);
	t = 1.0 - cos;
	mat = mat_angle(axis, cos, sin, t);
	return (mat);
}

t_mat	rotx_mat_init(double degrees)
{
	t_mat	rotationmat;
	double	rad;
	double	cos;
	double	sin;

	rad = deg2rad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmat = identity_mat_init();
	rotationmat.mat[1][1] = cos;
	rotationmat.mat[1][2] = -sin;
	rotationmat.mat[2][1] = sin;
	rotationmat.mat[2][2] = cos;
	return (rotationmat);
}

t_mat	roty_mat_init(double degrees)
{
	t_mat	rotationmat;
	double	rad;
	double	cos;
	double	sin;

	rad = deg2rad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmat = identity_mat_init();
	rotationmat.mat[0][0] = cos;
	rotationmat.mat[0][2] = sin;
	rotationmat.mat[2][0] = -sin;
	rotationmat.mat[2][2] = cos;
	return (rotationmat);
}

t_mat	rotz_mat_init(double degrees)
{
	t_mat	rotationmat;
	double	rad;
	double	cos;
	double	sin;

	rad = deg2rad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmat = identity_mat_init();
	rotationmat.mat[0][0] = cos;
	rotationmat.mat[0][1] = -sin;
	rotationmat.mat[1][0] = sin;
	rotationmat.mat[1][1] = cos;
	return (rotationmat);
}
