/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:15:16 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/06 12:15:19 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

double	rad(int deg)
{
	return (deg * M_PI / FLAT_ANGLE);
}

double	deg(double rad)
{
	return (rad * FLAT_ANGLE / M_PI);
}

double	tan(double x)
{
	return (sin(x) / cos(x));
}
