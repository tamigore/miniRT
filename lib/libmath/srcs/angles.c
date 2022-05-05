/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:15:16 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 13:23:25 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

double	deg2rad(double deg)
{
	return (deg * M_PI / FLAT_ANGLE);
}

double	rad2deg(double rad)
{
	return (rad * FLAT_ANGLE / M_PI);
}

double	v_cos(t_vec a, t_vec b)
{
	return (v_dot(a, b) / v_len(a) * v_len(b));
}

void	swap(double *x, double *y)
{
	double	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}
