/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:11:33 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/21 18:10:53 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec		get_sph_normal(t_sph *sph, t_ray *ray)
{
	return (v_norm(v_sub(v_norm(ray->hit), sph->pos)));
}

t_vec	get_cyl_normal(t_cyl *cyl, t_ray *ray)
{
	float	t;
	t_vec	normal;

	normal = v_init(0, 0, 0, 0);
	t = interCylinder(ray, cyl, &normal);
	if (t > 0)
		return (normal);
	return (v_init(0, 0, 0, 0));
}

t_vec		get_tri_normal(t_tri *tri)
{
	return (v_norm(v_cross(v_sub(tri->p2, tri->p1), v_sub(tri->p3, tri->p1))));
}
