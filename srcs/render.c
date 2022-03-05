/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:11:21 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/05 15:59:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render(t_env *env)
{
	int		i;
	t_img	*head;
	t_cam	*tmp;

	i = 0;
	tmp = env->cam;
	env->img = init_img(env);
	head = env->img;
	while (i < env->nb_cam)
	{
		printf("creat image...\n");
		trace_ray(env, tmp);
		tmp = tmp->next;
		env->img = env->img->next;
		i++;
		if (i < env->nb_cam)
			env->img = init_img(env);
	}
	env->img = head;
	circle_img_list(env->img, head);
}
