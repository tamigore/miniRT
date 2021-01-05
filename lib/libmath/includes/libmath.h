/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:31:48 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/05 15:25:21 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define bool unsigned int
#define TRUE 1
#define FALSE 0
#define UNIT 1.0
#define ZERO 0.0
#define REV -1.0
#define HALF_ANGLE 90
#define FLAT_ANGLE 180
#define FULL_ANGLE 360


/*
** v2 = vector 2d
** v2 = {a, b};
*/

typedef struct	s_v2
{
	double		x;
	double		y;
}				t_v2;

/*
** v3 = vector 3d
** v3 = {a, b, c};
*/

typedef struct	s_v3
{
	double		x;
	double		y;
	double		z;
}				t_v3;

/*
** v4 = vector 4d
** v4 = {a, b, c, d};
*/

typedef struct	s_v4
{
	double		w;
	double		x;
	double		y;
	double		z;
}				t_v4;

/*
** mat3 = matrice 3x3
**
** \ a b c
** x 0 0 0
** y 0 0 0
** Z 0 0 0
*/

typedef struct	s_mat3
{
	double		x[3];
	double		y[3];
	double		z[3];
	double		a[3];
	double		b[3];
	double		c[3];
}				t_mat3;

/*
** mat4 = matrice 4x4
**
** \ a b c d
** w 0 0 0 0
** x 0 0 0 0
** y 0 0 0 0
** z 0 0 0 0
*/

typedef struct	s_mat4
{
	double		w[4];
	double		x[4];
	double		y[4];
	double		z[4];
	double		a[4];
	double		b[4];
	double		c[4];
	double		d[4];
}				t_mat4;

/*
** VECTOR.C
*/
t_v3			v_init(double x, double y, double z);
t_v3			v_add(t_v3 a, t_v3 b);
t_v3			v_sub(t_v3 a, t_v3 b);
t_v3			v_cross(t_v3 a, t_v3 b);
t_v3			v_multi(double x, t_v3 a);

//VECTOR_2.C

t_v3			v_prod(t_v3 a, t_v3 b);
double			v_len(t_v3 v);
t_v3			v_norm(t_v3 vec);
double			v_dot(t_v3 a, t_v3 b);
int				v_comp(t_v3 u, t_v3 v);

//ANGLES.C

double			rad(int deg);
double			tan(double x);

#endif
