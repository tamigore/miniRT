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

t_vec	vec_prod(t_vec a, t_vec b)
{
	t_vec vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	vec.w = a.w * b.w;
	return (vec);
}

int		vec_comp(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	else
		return (0);
}

float	vec_len(t_vec v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vec	vec_norm(t_vec vec)
{
	vec.x = vec.x / vec_len(vec);
	vec.y = vec.y / vec_len(vec);
	vec.z = vec.z / vec_len(vec);
	vec.w = 0;
	return (vec);
}

float	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
