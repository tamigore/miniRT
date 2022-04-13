/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:11:21 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/13 17:30:55 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
			if (x == (unsigned int)env->res.x / 2 && y == (unsigned int)env->res.y /2)
				print_ray(&ray);
			put_pixel_to_image(env->cam->img, ray.color, x, y);
			x++;
		}
		y++;
	}
}

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
