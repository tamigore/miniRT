/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:17:14 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 18:10:35 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_env(t_env *env)
{
	printf("res :%d.x/%d.y\n", env->res.x, env->res.y);
	printf("amb :%.0f.R/%.0f.G/%.0f.B // %.2f.ratio\n", env->amb.color.x,
		env->amb.color.y, env->amb.color.z, env->amb.ratio);
	print_cam(env->cam);
	print_lgt(env->lgt);
	print_obj(env->obj);
}

void	print_cam(t_cam *cam)
{
	t_cam	*tmp;

	if (cam)
	{
		tmp = cam;
		while (tmp)
		{
			printf("cam :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz \
				//%d.fov\n", tmp->pos.x, tmp->pos.y,
				tmp->pos.z, tmp->dir.x, tmp->dir.y, tmp->dir.z, tmp->fov);
			tmp = tmp->next;
		}
	}
	else
		printf("cam :NULL\n");
}

void	print_lgt(t_lgt *lgt)
{
	t_lgt	*tmp;

	if (lgt)
	{
		tmp = lgt;
		while (tmp)
		{
			printf("lgt :%.2f.x/%.2f.y/%.2f.z // %f.ratio // \
				%.0f.R/%.0f.G/%.0f.B\n", tmp->pos.x, tmp->pos.y, tmp->pos.z,
				tmp->ratio, tmp->color.x, tmp->color.y, tmp->color.z);
			tmp = tmp->next;
		}
	}
	else
		printf("lgt :NULL\n");
}

void	print_ray(t_ray *ray)
{
	if (ray)
	{
		printf("ray :%.2f.x/%.2f.y/%.2f.z//%.2f.vx/%.2f.vy/%.2f.vz//t=%f\n",
			ray->pos.x, ray->pos.y, ray->pos.z, ray->dir.x,
			ray->dir.y, ray->dir.z, ray->t);
	}
	else
		printf("ray :NULL\n");
}

void	print_matrix(t_mat mat)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%4.2f", mat.mat[j++][i]);
			if (j != 4)
				printf(" |");
		}
		printf("\n");
		i++;
	}
}
