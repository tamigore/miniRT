/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:17:27 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/06 12:20:24 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

double	ft_pow(double x, int i)
{
	double	nb;

	if (x == 0)
		return (1);
	nb = 1;
	while (i-- > 0)
	{
		nb *= x;
	}
	return (nb);
}

int	sign(double x)
{
	if (x >= 0)
		return (1);
	return (-1);
}
