/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:56:45 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 19:11:07 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat		mat_mult_mat(t_mat a, t_mat b)
{
	t_mat	c;
	int		x;
	int		y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			c.mat[y][x] = a.mat[y][0] * b.mat[0][x]
				+ a.mat[y][1] * b.mat[1][x]
				+ a.mat[y][2] * b.mat[2][x]
				+ a.mat[y][3] * b.mat[3][x];
			x++;
		}
		y++;
	}
	return (c);
}

t_vec			mat_mult_vec(t_mat a, t_vec b)
{
	t_vec		c;

	c.x = a.mat[0][0] * b.x + a.mat[0][1] * b.y + a.mat[0][2] * b.z
		+ a.mat[0][3] * b.w;
	c.y = a.mat[1][0] * b.x + a.mat[1][1] * b.y + a.mat[1][2] * b.z
		+ a.mat[1][3] * b.w;
	c.z = a.mat[2][0] * b.x + a.mat[2][1] * b.y + a.mat[2][2] * b.z
		+ a.mat[2][3] * b.w;
	c.w = a.mat[3][0] * b.x + a.mat[3][1] * b.y + a.mat[3][2] * b.z
		+ a.mat[3][3] * b.w;
	return (c);
}
