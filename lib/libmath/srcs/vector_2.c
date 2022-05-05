/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:14:45 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/03 19:24:06 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec	v_prod(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	vec.w = a.w * b.w;
	return (vec);
}

int	v_comp(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	else
		return (0);
}

double	v_len(t_vec v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec	v_norm(t_vec vec)
{
	double	len;

	len = v_len(vec);
	vec.x = vec.x / len;
	vec.y = vec.y / len;
	vec.z = vec.z / len;
	vec.w = 0;
	return (vec);
}

double	v_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
