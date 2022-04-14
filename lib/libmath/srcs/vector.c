/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:14:26 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/14 17:12:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec	vec_init(float x, float y, float z, float w)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	vec.w = a.w + b.w;
	return (vec);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	vec.w = a.w - b.w; 
	return (vec);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	vec.w = 0;
	return (vec);
}

t_vec	vec_scale(float x, t_vec a)
{
	t_vec	vec;

	vec.x = a.x * x;
	vec.y = a.y * x;
	vec.z = a.z * x;
	vec.w = a.w * x;
	return (vec);
}
