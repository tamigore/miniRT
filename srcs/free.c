/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:10:05 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 19:18:49 by tamigore         ###   ########.fr       */
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

void	free_env(t_env *env)
{
	printf("free start\n");
	if (!env)
		return ;
	printf("win\n");
	if (env->mlx && env->win)
		mlx_destroy_window(env->mlx, env->win);
	printf("cam\n");
	if (env->cam)
		free_cam(env->cam, env->mlx);
	printf("lights\n");
	if (env->lgt)
		free_lgt(env->lgt);
	printf("objs\n");
	if (env->obj)
		free_obj(env->obj);
	printf("mlx\n");
	if (env->mlx)
	{
		mlx_destroy(env->mlx);
		free(env->mlx);
	}
	printf("env...\n");
	free(env);
}
