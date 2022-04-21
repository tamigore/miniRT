/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:51:20 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/21 14:09:07 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			trace_sph(t_sph *sph, t_ray *ray)
{
	int		hit;
	float	t;

	hit = 0;
	t = INFINITY;
	if ((sphere_intersect(sph, ray, &t)))
	{
		if (ray->t > t && t > EPSILON)
		{
			ray->t = t;
			hit = 1;
		}
	}
	return (hit);
}

int			trace_pla(t_pla *pla, t_ray *ray)
{
	int		hit;
	float	t;

	hit = 0;
	t = INFINITY;
	if ((plane_intersect(pla, ray, &t)))
	{
		if (ray->t > t && t > EPSILON)
		{
			ray->t = t;
			hit = 1;
		}
	}
	return (hit);
}

int			trace_cyl(t_cyl *cyl, t_ray *ray)
{
	int		hit;
	float	t;

	hit = 0;
	t = INFINITY;
	if ((cylinder_intersect(cyl, ray, &t)))
	{
		if (ray->t > t && t > EPSILON)
		{
			ray->t = t;
			hit = 1;
		}
	}
	return (hit);
}

int			trace_tri(t_tri *tri, t_ray *ray)
{
	int		hit;
	float	t;

	hit = 0;
	t = INFINITY;
	if ((triangle_intersect(tri, ray, &t)))
	{
		if (ray->t > t && t > EPSILON)
		{
			ray->t = t;
			hit = 1;
		}
	}
	return (hit);
}
