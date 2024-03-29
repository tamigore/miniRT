/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_rmchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 14:39:00 by tamigore          #+#    #+#             */
/*   Updated: 2019/08/08 14:39:34 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_free_rmchar(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == c)
			j++;
		i++;
	}
	new = ft_strnew(i);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		new[j++] = str[i++];
		if (str[i - 1] == c)
			j--;
	}
	free(str);
	return (new);
}
