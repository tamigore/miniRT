/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:00:55 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 18:17:00 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char *s1, char *s2, int r)
{
	char	*join;
	int		diff;
	char	*tmp;

	tmp = s1;
	diff = ft_strlen(s2) - r;
	if (!s1 || !s2)
		return (NULL);
	join = ft_strnew(ft_strlen(s1) + ft_strlen(s2) - diff);
	if (!join)
		return (NULL);
	ft_strncat(join, s1, ft_strlen(s1));
	ft_strncat(join, s2, r);
	free(tmp);
	return (join);
}
