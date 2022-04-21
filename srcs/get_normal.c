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
	return (vec_norm(vec_sub(vec_norm(ray->hit), sph->pos)));
}

t_vec	get_cyl_normal(t_cyl *cyl, t_ray *ray)
{
	t_vec		r;
	t_vec		n;
	float		rp_cp_ch;
	t_vec		ca;

	ca = vec_sub(vec_scale(-cyl->h, cyl->dir), vec_scale(cyl->h, cyl->dir));
	rp_cp_ch = vec_dot(ca, vec_sub(ray->pos, cyl->pos));
	rp_cp_ch += ray->t * vec_dot(ca, ray->dir);
	if (!(rp_cp_ch < vec_dot(ca, ca)))
		return (cyl->dir);
	else
	{
		r = vec_scale(ray->t, ray->dir);
		n = vec_sub(r, cyl->pos);
		n = vec_cross(n, cyl->dir);
		n = vec_norm(vec_cross(n, cyl->dir));
		return (n);
	}
}

t_vec		get_tri_normal(t_tri *tri)
{
	return (vec_norm(vec_cross(vec_sub(tri->p2, tri->p1), vec_sub(tri->p3, tri->p1))));
}
