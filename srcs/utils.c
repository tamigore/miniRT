/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:07:28 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/11 19:37:19 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int		rgb2color(int R, int G, int B)
{
	return ((R<<16)|(G<<8)|B);
}

int		correct_line(char *txt)
{
	if (!ft_strncmp(txt, "R ", 2) || !ft_strncmp(txt, "A ", 2) ||
		!ft_strncmp(txt, "l ", 2) || !ft_strncmp(txt, "c ", 2) ||
		!ft_strncmp(txt, "tr ", 3) || !ft_strncmp(txt, "cy ", 3) ||
		!ft_strncmp(txt, "sq ", 3) || !ft_strncmp(txt, "sp ", 3))
		return (1);
	return (0);
}

void	fast_exit(char *str, int i)
{
	perror(str);
	exit(i);
}
