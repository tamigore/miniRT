/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:31:48 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/06 18:13:09 by tamigore         ###   ########.fr       */
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

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_v3;

/*
** m4 = matrice 4x4
**
** \ w x y z
** a 0 0 0 0
** b 0 0 0 0
** c 0 0 0 0
** d 0 0 0 0
*/

typedef struct	s_m4
{
	double		m[4][4];
	double		w[4];
	double		x[4];
	double		y[4];
	double		z[4];
}				t_m4;

/*
** VECTOR.C
*/

t_v3			v_init(double x, double y, double z);
t_v3			v_add(t_v3 a, t_v3 b);
t_v3			v_sub(t_v3 a, t_v3 b);
t_v3			v_cross(t_v3 a, t_v3 b);
t_v3			v_multi(double x, t_v3 a);

/*
** VECTOR_2.C
*/

t_v3			v_prod(t_v3 a, t_v3 b);
double			v_len(t_v3 v);
t_v3			v_norm(t_v3 vec);
double			v_dot(t_v3 a, t_v3 b);
int				v_comp(t_v3 u, t_v3 v);

/*
** ANGLES.C
*/

double			rad(int deg);
double			tan(double x);

/*
** MATRIX.C
*/

t_m4			*mat_init(void);
void			mat_free(t_m4 *mat);
void			mat_fill(double *a, double *b, double *c, double *d, t_m4 *mat);
void			get_column(double *col, double mat[4][4], int i);
void			get_line(double *lin, double mat[4]);

/*
** MATRIX.C
*/

void			mat4Xmat4(t_m4 *a, t_m4 *b, t_m4 *mat);
double			tab4Xtab4(double a[4], double b[4]);
t_v3			vec3Xmat4(t_v3 vec, double M[4][4]);
int				mat_invers(double m[4][4], t_m4 *invert);

#endif
