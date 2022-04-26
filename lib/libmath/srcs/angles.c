/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:15:16 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 17:22:00 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

float	deg2rad(float deg)
{
	return (deg * M_PI / FLAT_ANGLE);
}

float	rad2deg(float rad)
{
	return (rad * FLAT_ANGLE / M_PI);
}

float	v_cos(t_vec a, t_vec b)
{
	return (v_dot(a, b) / v_len(a) * v_len(b));
}

void		swap(float *x, float *y)
{
	float	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}
