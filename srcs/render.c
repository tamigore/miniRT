/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:11:21 by tamigore          #+#    #+#             */
/*   Updated: 2021/03/17 17:47:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	render_n_img(t_env *env, int nb)
{
	int		i;
	t_img	*head;
	t_cam	*tmp;

	i = 0;
	tmp = env->cam;
	env->img = init_img(env);
	head = env->img;
	while (i < nb)
	{
		trace_ray(env, tmp);
		tmp = tmp->next;
		env->img = env->img->next;
		i++;
		if (i < nb)
			env->img = init_img(env);
	}
	env->img = head;
	circle_img_list(env->img, head);
}

int			render(t_env *env, int save)
{
	if (save)
	{
		render_n_img(env, 1);
		set_save(env, BMP_FILE);
	}
	render_n_img(env, env->nb_cam);
	return (1);
}
