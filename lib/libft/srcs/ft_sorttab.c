/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:31:54 by tamigore          #+#    #+#             */
/*   Updated: 2018/11/19 15:59:49 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sorttab(char **tab)
{
	int		x;
	char	*p;

	x = 0;
	while (tab[x + 1] != 0)
	{
		if (ft_strcmp(tab[x], tab[x + 1]) > 0)
		{
			p = tab[x];
			tab[x] = tab[x + 1];
			tab[x + 1] = p;
			x = 0;
		}
		else
			x++;
	}
}
