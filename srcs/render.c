/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:11:21 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/31 15:23:19 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
}
