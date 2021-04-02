/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:55:18 by tamigore          #+#    #+#             */
/*   Updated: 2021/03/11 15:56:12 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int		create_color(int trans, int red, int green, int blue)
{
	return(trans << 24 | red << 16 | green << 8 | blue);
}

unsigned int		get_trans(int color)
{
	return (color & (0xFF << 24));
}

unsigned int		get_red(int color)
{
	return (color & (0xFF << 16));
}

unsigned int		get_green(int color)
{
	return (color & (0xFF << 8));
}

unsigned int		get_blue(int color)
{
	return (color & 0xFF);
}
