/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:51:20 by tamigore          #+#    #+#             */
/*   Updated: 2021/02/11 17:46:44 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			trace_sph(t_sph *sph, t_ray *ray)
{
	int		hit;
	double	t;

	hit = 0;
	t = INFINITY;
	if ((sphere_intersect(sph, ray, &t)))
	{
		if (ray->t > t && t > 0)
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
	double	t;

	hit = 0;
	t = INFINITY;
	if ((plane_intersect(pla, ray, &t)))
	{
		if (ray->t > t && t > 0)
		{
			ray->t = t;
			hit = 1;
		}
	}
	return (hit);
}

int			trace_sqr(t_sqr *sqr, t_ray *ray)
{
	int		hit;
	double	t;

	hit = 0;
	t = INFINITY;
	if ((square_intersect(sqr, ray, &t)))
	{
		if (ray->t > t && t > 0)
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
	double	t;

	hit = 0;
	t = INFINITY;
	if ((cylinder_intersect(cyl, ray, &t)))
	{
		if (ray->t > t && t > 0)
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
	double	t;

	hit = 0;
	t = INFINITY;
	if ((triangle_intersect(tri, ray, &t)))
	{
		if (ray->t > t && t > 0)
		{
			ray->t = t;
			hit = 1;
		}
	}
	return (hit);
}
