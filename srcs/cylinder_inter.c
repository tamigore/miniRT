/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/02 13:23:25 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	interCylinder(t_ray *ray, t_cyl *cyl, t_vec *normal) // extreme a, extreme b, radius
{
    t_vec	ba = v_sub(v_add(v_scale(cyl->h, v_norm(cyl->dir)), cyl->pos), cyl->pos);
    t_vec	oc = v_sub(ray->pos, cyl->pos);
	t_vec	angle = v_init(v_dot(ba,ba), v_dot(ba, v_norm(ray->dir)), v_dot(ba,oc), 0);
    
    double k2 = angle.x - angle.y * angle.y;
    double k1 = angle.x * v_dot(oc, v_norm(ray->dir)) - angle.z * angle.y;
    double k0 = angle.x * v_dot(oc, oc) - angle.z * angle.z - cyl->r * cyl->r * angle.x;
    
    double h = k1 * k1 - k2 * k0;

    if (h < 0.0)
		return (0);
    h = sqrtf(h);
    double t = (-k1 - h) / k2;

    // body
    double y = angle.z + t * angle.y;
    if (y > 0.0 && y < angle.x)
	{
		*normal = v_scale(1 / cyl->r, v_sub(v_add(oc, v_scale(t, v_norm(ray->dir))), v_scale(y / angle.x, ba)));
		return (t);
	}
    // caps
    t = ( ((y < 0.0) ? 0.0 : angle.x) - angle.z) / angle.y;
    if(fabs(k1 + k2 * t) < h)
	{
		*normal = v_scale(1 / angle.x, v_scale(sign(y), ba));
        return (t);
	}
    return (0);
}

int		cylinder_intersect(t_cyl *cyl, t_ray *ray, double *t)
{
	t_vec normal;

	normal = v_init(0,0,0,0);
	*t = interCylinder(ray, cyl, &normal);
	if (t > 0)
		return (1);
	return (0);
}