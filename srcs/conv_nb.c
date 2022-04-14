/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_nb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 10:45:25 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 17:12:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	str_to_unsigned(t_env *env)
{
	float	nb;

	nb = 0;
	while (*(env->sceen) && (*(env->sceen) < '0' || *(env->sceen) > '9'))
		(env->sceen)++;
	while (*(env->sceen) && *(env->sceen) >= '0' && *(env->sceen) <= '9')
	{
		nb *= 10;
		nb += *(env->sceen) - '0';
		(env->sceen)++;
	}
	if (*(env->sceen) == ',')
		(env->sceen)++;
	return (nb);
}

float	str_to_long(t_env *env)
{
	int		minus;
	float	nb;

	minus = 1;
	while (*(env->sceen) && (*(env->sceen) < '0' || *(env->sceen) > '9'))
	{
		if (*(env->sceen) == '-')
			minus = -1;
		(env->sceen)++;
	}
	nb = str_to_unsigned(env);
	return (nb * minus);
}

float	str_to_float(t_env *env)
{
	int		minus;
	float	nb;
	float	inte;

	nb = 0;
	minus = 1;
	while (*(env->sceen) && (*(env->sceen) < '0' || *(env->sceen) > '9'))
	{
		if (*(env->sceen) == '-')
			minus = -1;
		(env->sceen)++;
	}
	inte = str_to_unsigned(env);
	if (*(env->sceen) == '.')
	{
		(env->sceen)++;
		nb = (float)str_to_unsigned(env);
		while (nb >= 1)
			nb /= 10;
	}
	nb += (float)inte;
	return (nb * minus);
}
