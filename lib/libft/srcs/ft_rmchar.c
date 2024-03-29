/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:37:13 by tamigore          #+#    #+#             */
/*   Updated: 2020/01/16 19:13:49 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_rmchar(char *str, char c)
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
		if (str[i] == c)
			j--;
	}
	free(str);
	return (new);
}
