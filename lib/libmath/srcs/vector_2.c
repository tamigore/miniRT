/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:14:45 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 17:12:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec	v_prod(t_vec a, t_vec b)
{
	t_vec vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	vec.w = a.w * b.w;
	return (vec);
}

int		v_comp(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	else
		return (0);
}

float	v_len(t_vec v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vec	v_norm(t_vec vec)
{
	vec.x = vec.x / v_len(vec);
	vec.y = vec.y / v_len(vec);
	vec.z = vec.z / v_len(vec);
	vec.w = 0;
	return (vec);
}

float	v_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
