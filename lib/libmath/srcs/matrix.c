/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:20:45 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 17:13:36 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat		identity_mat_init(void)
{
	t_mat	id;

	id.mat[0][0] = 1.0;
	id.mat[0][1] = 0.0;
	id.mat[0][2] = 0.0;
	id.mat[0][3] = 0.0;
	id.mat[1][0] = 0.0;
	id.mat[1][1] = 1.0;
	id.mat[1][2] = 0.0;
	id.mat[1][3] = 0.0;
	id.mat[2][0] = 0.0;
	id.mat[2][1] = 0.0;
	id.mat[2][2] = 1.0;
	id.mat[2][3] = 0.0;
	id.mat[3][0] = 0.0;
	id.mat[3][1] = 0.0;
	id.mat[3][2] = 0.0;
	id.mat[3][3] = 1.0;
	return (id);
}

t_mat		scale_mat_init(float scale)
{
	t_mat	scalemat;

	scalemat = identity_mat_init();
	scalemat.mat[0][0] *= scale;
	scalemat.mat[1][1] *= scale;
	scalemat.mat[2][2] *= scale;
	return (scalemat);
}

t_mat		translation_mat_init(t_vec tranvec)
{
	t_mat	translationmat;

	translationmat = identity_mat_init();
	translationmat.mat[0][3] = tranvec.x;
	translationmat.mat[1][3] = tranvec.y;
	translationmat.mat[2][3] = tranvec.z;
	return (translationmat);
}
