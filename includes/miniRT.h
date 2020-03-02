/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:30:18 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/02 20:42:32 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_H_
# define _MINIRT_H_

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>

#define DISPLAY_X 2560
#define DISPLAY_Y 1440
#define FAILURE -1
#define SUCCESS 1
#define END 0

typedef struct		s_cam
{
	float			x;
	float			y;
	float			z;
	int				fov;
	float			vx;
	float			vy;
	float			vz;
	struct s_cam	*next;
	struct s_cam	*prev;
}					t_cam;

typedef struct		s_res
{
	int				x;
	int				y;
}					t_res;

typedef struct		s_lum
{
	float			x;
	float			y;
	float			z;
	float			l;
	int				R;
	int				G;
	int				B;
	struct s_lum	*next;
	struct s_lum	*prev;
}					t_lum;

typedef struct		s_amb
{
	int				R;
	int				G;
	int				B;
	float			l;
}					t_amb;

typedef struct		s_pla
{
	float			x;
	float			y;
	float			z;
	float			vx;
	float			vy;
	float			vz;
	int				R;
	int				G;
	int				B;
	struct s_pla	*next;
	struct s_pla	*prev;
}					t_pla;

typedef struct		s_car
{
	float			x;
	float			y;
	float			z;
	float			h;
	float			vx;
	float			vy;
	float			vz;
	int				R;
	int				G;
	int				B;
	struct s_car	*next;
	struct s_car	*prev;
}					t_car;

typedef struct		s_cyl
{
	float			x;
	float			y;
	float			z;
	float			h;
	float			d;
	float			vx;
	float			vy;
	float			vz;
	int				R;
	int				G;
	int				B;
	struct s_cyl	*next;
	struct s_cyl	*prev;
}					t_cyl;

typedef struct		s_tri
{
	float			x1;
	float			y1;
	float			z1;
	float			x2;
	float			y2;
	float			z2;
	float			x3;
	float			y3;
	float			z3;
	int				R;
	int				G;
	int				B;
	struct s_tri	*next;
	struct s_tri	*prev;
}					t_tri;

typedef struct		s_sph
{
	float			x;
	float			y;
	float			z;
	float			d;
	int				R;
	int				G;
	int				B;
	struct s_sph	*next;
	struct s_sph	*prev;
}					t_sph;

typedef struct		s_env
{
	struct s_cam	*cam;
	struct s_res	*res;
	struct s_lum	*lum;
	struct s_amb	*amb;
	struct s_car	*car;
	struct s_pla	*pla;
	struct s_tri	*tri;
	struct s_cyl	*cyl;
	struct s_sph	*sph;
}					t_env;

/*
**	miniRT.c
*/

t_env		*init_env(char *av);
void		pars(char *txt, t_env **env);
void		print_env(t_env *env);
int			correct_line(char *txt);

/*
** OBJ
*/

t_res		*resolution(char *txt);
t_amb		*ambiance(char *txt);
t_cam		*camera(char *txt);
t_lum		*lumiere(char *txt);
t_cyl		*cylindre(char *txt);
t_tri		*triangle(char *txt);
t_car		*carre(char *txt);
t_pla		*plane(char *txt);
t_sph		*sphere(char *txt);

/*
** Conv_nb.c
*/

double		str_to_double(char *str, int *i);
long long	str_to_long(char *str, int *i);
unsigned	str_to_unsigned(char *str, int len);

#endif
