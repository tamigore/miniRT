/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:11:33 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 18:09:10 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec		get_sph_normal(t_sph *sph, t_ray *ray)
{
	return (vec_norm(vec_sub(vec_norm(ray->hit), sph->pos)));
}

t_vec		get_cyl_normal(t_cyl *cyl, t_ray *ray)
{
	t_vec	tmp;
	t_vec	res;

	tmp = vec_sub(ray->hit, cyl->pos);
	res = vec_norm(vec_sub(tmp, vec_scale(vec_dot(cyl->dir, tmp), cyl->dir)));
	return (res);
}

t_vec		get_tri_normal(t_tri *tri)
{
	return (vec_norm(vec_cross(vec_sub(tri->p2, tri->p1), vec_sub(tri->p3, tri->p1))));
}
