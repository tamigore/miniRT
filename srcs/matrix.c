/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:56 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/08 10:44:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (!(mat_invers(inv, cam2world)))
		return (NULL);
	mat_free(mat);
	mat_free(tmp);
	return (cam2world);
}
