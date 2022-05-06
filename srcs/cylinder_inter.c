/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 18:54:29 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_angle_coef(t_ray *r, t_cyl *c, t_vec *k, t_vec *angle)
{
	t_vec	ba;
	t_vec	oc;

	oc = v_sub(r->pos, c->pos);
	ba = v_sub(v_add(v_scale(c->h, v_norm(c->dir)), c->pos), c->pos);
	*angle = v_init(v_dot(ba, ba), v_dot(ba, v_norm(r->dir)), v_dot(ba, oc), 0);
	k->x = angle->x - angle->y * angle->y;
	k->y = angle->x * v_dot(oc, v_norm(r->dir)) - angle->z * angle->y;
	k->z = angle->x * v_dot(oc, oc) - angle->z * angle->z - c->r * c->r
		* angle->x;
}

t_vec	get_cyl_n1(t_ray *r, t_cyl *c, t_vec tmp, t_vec angle)
{
	t_vec	new_1;
	t_vec	new_2;

	new_1 = v_sub(v_add(v_scale(c->h, v_norm(c->dir)), c->pos), c->pos);
	new_2 = v_add(v_sub(r->pos, c->pos), v_scale(tmp.y, v_norm(r->dir)));
	return (v_scale(1 / c->r, v_sub(new_2, v_scale(tmp.z / angle.x, new_1))));
}

int	init_tmp(t_vec *tmp, t_vec angle, t_vec k)
{
	tmp->x = k.y * k.y - k.z * k.x;
	if (tmp->x < 0.0)
		return (0);
	tmp->x = sqrtf(tmp->x);
	tmp->y = (-k.y - tmp->x) / k.x;
	tmp->z = angle.z + tmp->y * angle.y;
	return (1);
}

double	inter_cylinder(t_ray *r, t_cyl *c, t_vec *normal)
{
	t_vec	angle;
	t_vec	k;
	t_vec	tmp;
	t_vec	new;

	get_angle_coef(r, c, &k, &angle);
	if (!init_tmp(&tmp, angle, k))
		return (0);
	if (tmp.z > 0.0 && tmp.z < angle.x)
	{
		*normal = get_cyl_n1(r, c, tmp, angle);
		return (tmp.y);
	}
	tmp.y = (angle.x - angle.z) / angle.y;
	if (tmp.z < 0.0)
		tmp.y = -angle.z / angle.y;
	if (fabs(k.y + k.x * tmp.y) < tmp.x)
	{
		new = v_sub(v_add(v_scale(c->h, v_norm(c->dir)), c->pos), c->pos);
		*normal = v_scale(1 / angle.x, v_scale(sign(tmp.z), new));
		return (tmp.y);
	}
	return (0);
}

int	cylinder_intersect(t_cyl *cyl, t_ray *ray, double *t)
{
	t_vec	normal;

	normal = v_init(0, 0, 0, 0);
	*t = inter_cylinder(ray, cyl, &normal);
	if (t > 0)
		return (1);
	return (0);
}
