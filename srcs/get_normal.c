/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:11:33 by tamigore          #+#    #+#             */
/*   Updated: 2021/02/03 15:14:29 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3		get_sph_normal(t_sph *sph, t_ray *ray)
{
	return (v_norm(v_sub(ray->hit, sph->pos)));
}

t_v3		get_cyl_normal(t_cyl *cyl, t_ray *ray)
{
	t_v3	tmp;
	t_v3	res;

	tmp = v_sub(ray->hit, cyl->pos);
	res = v_norm(v_sub(tmp, v_multi(v_dot(cyl->dir, tmp), cyl->dir)));
	return (res);
}

t_v3		get_tri_normal(t_tri *tri)
{
	return (v_norm(v_cross(v_sub(tri->p2, tri->p1), v_sub(tri->p3, tri->p1))));
}
