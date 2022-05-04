/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:11:21 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 19:18:34 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	trace_ray : Does all the raytracing.
*/

void				trace_ray(t_env *env)
{
	unsigned int	x;
	unsigned int	y;
	t_ray			ray;

	y = 0;
	while (y < (unsigned int)env->res.y -1)
	{
		x = 0;
		while (x < (unsigned int)env->res.x - 1)
		{
			ray = canvas2view(env, env->cam, x, y);
			shade(env, &ray);
			put_pixel_to_image(env->cam->img, ray.color, x, y);
			x++;
		}
		y++;
		printf("render : %d sur %d\n", y * env->res.x + x, env->res.y * env->res.x);
	}
	print_ray(&ray);
}

/*
**	init_img : init mlx image.
*/

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

/*
**	render : init and render one image per camera.
*/

void	render(t_env *env)
{
	int		i;
	t_cam	*tmp;

	i = 0;
	tmp = env->cam;
	env->cam->img = init_img(env);
	while (i < env->nb_cam)
	{
		printf("creat image...\n");
		trace_ray(env);
		i++;
		if (i < env->nb_cam)
		{
			env->cam = env->cam->next;
			env->cam->img = init_img(env);
		}
		else
			break ;
	}
	env->cam->next = tmp;
	env->cam = env->cam->next;
}
