/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:10:05 by tamigore          #+#    #+#             */
/*   Updated: 2022/03/31 15:37:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_cam(t_cam *cam, void *mlx_ptr)
{
	t_cam	*tmp;
	t_cam	*head;

	if (cam)
	{
		head = cam;
		while (cam)
		{
			tmp = cam;
			cam = cam->next;
			if (tmp->img.ptr)
				mlx_destroy_image(mlx_ptr, tmp->img.ptr);
			free(tmp);
			if (cam == head)
				cam = NULL;
		}
	}
}

static void	free_lgt(t_lgt *lgt)
{
	t_lgt	*tmp;
	t_lgt	*head;

	if (lgt)
	{
		head = lgt;
		while (lgt)
		{
			tmp = lgt;
			lgt = lgt->next;
			free(tmp);
			if (lgt == head)
				lgt = NULL;
		}
	}
}

static void	free_obj(t_obj *obj)
{
	t_obj	*tmp;
	t_obj	*head;

	if (obj)
	{
		head = obj;
		while (obj)
		{
			tmp = obj;
			obj = obj->next;
			free(tmp->data);
			free(tmp);
			if (obj == head)
				obj = NULL;
		}
	}
}

void		free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->mlx)
		mlx_destroy_window(env->mlx, env->win);
	free_cam(env->cam, env->mlx);
	free_lgt(env->lgt);
	free_obj(env->obj);
	free(env->mlx);
	free(env);
}
