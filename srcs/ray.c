/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:26:22 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/05 19:21:17 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	reset_ray(t_ray *ray)
{
	ray->t = INFINITY;
	ray->color = v_init(0, 0, 0, 0);
	ray->hit = v_init(0, 0, 0, 0);
	ray->normal = v_init(0, 0, 0, 0);
}

void	set_ray(t_ray *ray, t_vec pos, t_vec dir, double t)
{
	ray->pos = pos;
	ray->dir = dir;
	ray->t = t;
}

void	init_ray(t_ray *ray)
{
	set_ray(ray, v_init(0, 0, 0, 0), v_init(0, 0, 0, 0), 0);
	reset_ray(ray);
}
