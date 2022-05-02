/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:07:28 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 13:23:25 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec	rescale_vec(t_vec vec, int min, int max)
{
	if (vec.x > max)
		vec.x = max;
	if (vec.y > max)
		vec.y = max;
	if (vec.z > max)
		vec.z = max;
	if (vec.x < min)
		vec.x = min;
	if (vec.y < min)
		vec.y = min;
	if (vec.z < min)
		vec.z = min;
	return (vec);
}

int		check_val(double val, double min, double max)
{
	if (val > max)
		return (0);
	if (val < min)
		return (0);
	return (1);
}

int		check_vec(t_vec vec)
{
	if ((vec.x == 0 && vec.y == 0 && vec.z == 0 )
		|| (!check_val(vec.x, -1, 1) || !check_val(vec.y, -1, 1)
		|| !check_val(vec.z, -1, 1)))
		return (0);
	return (1);
}

char	*ft_strjoindelone(char *s1, char *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = 0;
	len_s2 = 0;
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = ft_strlen(s2);
	result = ft_strnew(len_s1 + len_s2);
	if (!result)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(result, s1, (len_s1 + 1));
		ft_strdel(&s1);
	}
	if (s2)
		ft_strlcpy(result + len_s1, s2, (len_s2 + 1));
	return (result);
}

int		rgb2color(int R, int G, int B)
{
	return ((R<<16)|(G<<8)|B);
}
