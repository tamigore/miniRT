/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_nb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 10:45:25 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/02 17:19:55 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

unsigned	str_to_unsigned(char *str, int len)
{
	unsigned	nb;
	size_t		i;

	i = 0;
	nb = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9' && i < len)
	{
		nb *= 10;
		nb += str[i++] - '0';
	}
	return (nb);
}

long long	str_to_long(char *str, int *i)
{
	int			j;
	int			minus;
	long long	nb;

	minus = 1;
	while (str[*i] && (str[*i] < '0' || str[*i] > '9'))
	{
		if (str[*i] == '-')
			minus = -1;
		(*i)++;
	}
	j = *i;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
		(*i)++;
	nb = str_to_unsigned(&str[j], *i - j);
	return (nb * minus);
}

double		str_to_double(char *str, int *i)
{
	int			j;
	int			minus;
	double		nb;
	long long	inte;

	nb = 0;
	minus = 1;
	while (str[*i] && (str[*i] < '0' || str[*i] > '9'))
	{
		if (str[*i] == '-')
			minus = -1;
		(*i)++;
	}
	j = *i;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
		(*i)++;
	inte = str_to_unsigned(&str[j], *i - j);
	if (str[*i] == '.')
	{
		j = ++(*i);
		while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
			(*i)++;
		nb = (double)str_to_unsigned(&str[j], *i - j);
		while (*i > j)
		{
			nb /= 10;
			j++;
		}
	}
	nb += (double)inte;
	return (nb * minus);
}
