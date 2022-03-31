/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:33:11 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/31 15:23:47 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_img		init_img(t_env *env)
{
	t_img	img;

	img.size_x = env->res.x;
	img.size_y = env->res.y;
	img.bpp = 32;
	img.size_line = (img.bpp / 8) * img.size_x;
	img.endian = 0;
	img.ptr = mlx_new_image(env->mlx, img.size_x, img.size_y);
	img.pixels = mlx_get_data_addr(img.ptr, &(img.bpp),
				&(img.size_line), &(img.endian));
	return (img);
}
