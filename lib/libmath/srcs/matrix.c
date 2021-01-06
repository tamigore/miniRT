/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:20:45 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/06 17:39:21 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_m4		*mat_init(void)
{
	t_m4	*mat;
	int		i;
	double	nul[4];

	nul[0] = 0;
	nul[1] = 0;
	nul[2] = 0;
	nul[3] = 0;
	mat = (t_m4 *)malloc(sizeof(t_m4));
	if (mat == NULL)
		return (NULL);
	i = 0;
	while (i < 4)
		get_line(mat->m[i++], nul);
	get_line(mat->w, nul);
	get_line(mat->x, nul);
	get_line(mat->y, nul);
	get_line(mat->z, nul);
	return (mat);
}

void		mat_free(t_m4 *mat)
{
	int		i;
	double	nul[4];

	nul[0] = 0;
	nul[1] = 0;
	nul[2] = 0;
	nul[3] = 0;
	i = 0;
	while (i < 4)
		get_line(mat->m[i++], nul);
	get_line(mat->w, nul);
	get_line(mat->x, nul);
	get_line(mat->y, nul);
	get_line(mat->z, nul);
	free(mat);
}

void		mat_fill(double a[4], double b[4], double c[4], double d[4], t_m4 *mat)
{
	get_line(mat->m[0], a);
	get_line(mat->m[1], b);
	get_line(mat->m[2], c);
	get_line(mat->m[3], d);
	get_column(mat->w, mat->m, 0);
	get_column(mat->x, mat->m, 1);
	get_column(mat->y, mat->m, 2);
	get_column(mat->z, mat->m, 3);
}

void		get_column(double col[4], double mat[4][4], int i)
{
	col[0] = mat[0][i];
	col[1] = mat[1][i];
	col[2] = mat[2][i];
	col[3] = mat[3][i];
}

void		get_line(double lin[4], double mat[4])
{
	lin[0] = mat[0];
	lin[1] = mat[1];
	lin[2] = mat[2];
	lin[3] = mat[3];
}
