/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:13:32 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 18:21:49 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	if (j > 0)
		j--;
	while (ft_search((char *)set, s1[i]))
		i++;
	while (ft_search((char *)set, s1[j]) && j >= i)
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!str)
		return (NULL);
	n = 0;
	while (i <= j)
		str[n++] = s1[i++];
	str[n] = '\0';
	return (str);
}
