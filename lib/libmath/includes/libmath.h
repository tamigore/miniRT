/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:31:48 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/12 18:09:09 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define TRUE 1
# define FALSE 0
# define UNIT 1.0
# define ZERO 0.0
# define REV -1.0
# define HALF_ANGLE 90
# define FLAT_ANGLE 180
# define FULL_ANGLE 360

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
** vec = vector 4d
** vec = {a, b, c, d};
** to use operation with 4x4 matrix
*/

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec;

/*
** m4 = matrice 4x4
**
** \ w x y z
** a 0 0 0 0
** b 0 0 0 0
** c 0 0 0 0
** d 0 0 0 0
*/

typedef struct	t_mat
{
	double		mat[4][4];
}				t_mat;

/*
** VECTOR.C vector basics
*/

t_vec			vec_init(double x, double y, double z, double w);
t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_sub(t_vec a, t_vec b);
t_vec			vec_cross(t_vec a, t_vec b);
t_vec			vec_scale(double x, t_vec a);

/*
** VECTOR_2.C vector operation
*/

t_vec			vec_prod(t_vec a, t_vec b);
int				vec_comp(t_vec a, t_vec b);
double			vec_len(t_vec v);
t_vec			vec_norm(t_vec vec);
double			vec_dot(t_vec a, t_vec b);

/*
** ANGLES.C trigo basics
*/

double			deg2rad(double deg);
double			rad2deg(double rad);
double			tan(double x);
double			vec_cos(t_vec a, t_vec b);
void			swap(double *x, double *y);

/*
** MATRIX.C matrix init and fill
*/

t_mat	identity_mat_init(void);
t_mat	scale_mat_init(float scale);
t_mat	translation_mat_init(t_vec tranvec);

/*
** MATRIX_OP.C operation matrix
*/

t_mat	mat_mult_mat(t_mat a, t_mat b);
t_vec	vec_mult_mat(t_vec vec, t_mat m);

/*
** MATRIX_TR.C matrix transformation and rotation
*/

t_mat	mat_axis_angle_get(t_vec axis, float cos, float sin, float t);
t_mat	rotmat_axis_angle(t_vec axis, float angle);
t_mat	rotx_mat_init(float degrees);
t_mat	roty_mat_init(float degrees);
t_mat	rotz_mat_init(float degrees);

#endif
