/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:26:22 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 18:06:12 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		reset_ray(t_ray *ray)
{
	ray->t = INFINITY;
	ray->color = vec_init(0, 0, 0, 0);
	ray->hit = vec_init(0, 0, 0, 0);
	ray->normal = vec_init(0, 0, 0, 0);
}

void		set_ray(t_ray *ray, t_vec pos, t_vec dir, double t)
{
	ray->pos = pos;
	ray->dir = dir;
	ray->t = t;
}

void		init_ray(t_ray *ray)
{
	set_ray(ray, vec_init(0, 0, 0, 0), vec_init(0, 0, 0, 0), 0);
	reset_ray(ray);
}
