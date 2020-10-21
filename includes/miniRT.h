/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:30:18 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/11 19:37:21 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_H_
# define _MINIRT_H_

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include "libft.h"
#include "libgeo.h"
#include <math.h>
#include <stdio.h>

#define MAX_DEPTH 100
#define DISPLAY_X 1200	//2560
#define DISPLAY_Y 800	//1440
#define FAILURE -1
#define SUCCESS 1
#define END 0

typedef struct		s_cam
{
	double			x;
	double			y;
	double			z;
	int				fov;
	double			vx;
	double			vy;
	double			vz;
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
	double			x;
	double			y;
	double			z;
	double			l;
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
	double			l;
}					t_amb;

typedef struct		s_pla
{
	double			x;
	double			y;
	double			z;
	double			vx;
	double			vy;
	double			vz;
	int				R;
	int				G;
	int				B;
	struct s_pla	*next;
	struct s_pla	*prev;
}					t_pla;

typedef struct		s_car
{
	double			x;
	double			y;
	double			z;
	double			h;
	double			vx;
	double			vy;
	double			vz;
	int				R;
	int				G;
	int				B;
	struct s_car	*next;
	struct s_car	*prev;
}					t_car;

typedef struct		s_cyl
{
	double			x;
	double			y;
	double			z;
	double			h;
	double			d;
	double			vx;
	double			vy;
	double			vz;
	int				R;
	int				G;
	int				B;
	struct s_cyl	*next;
	struct s_cyl	*prev;
}					t_cyl;

typedef struct		s_tri
{
	double			x1;
	double			y1;
	double			z1;
	double			x2;
	double			y2;
	double			z2;
	double			x3;
	double			y3;
	double			z3;
	int				R;
	int				G;
	int				B;
	struct s_tri	*next;
	struct s_tri	*prev;
}					t_tri;

typedef struct		s_sph
{
	double			x;
	double			y;
	double			z;
	double			d;
	int				R;
	int				G;
	int				B;
	struct s_sph	*next;
	struct s_sph	*prev;
}					t_sph;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*ima;
	char			*adr;
}					t_mlx;

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
	struct s_mlx	*mlx;
}					t_env;

/*
**	miniRT.c
*/

t_env		*init_env(char *av);
void		pars(char *txt, t_env **env);
void 		reset_env(t_env **env);
void		print_env(t_env *env);

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

/*
** mlx.c
*/

int		mlx_creat_all(t_env **env);
int		win_pixel(t_env *env, int x, int y);
t_v3		cam_pixel(t_env *env, int x, int y);

/*
** utils.c
*/

int		rgb2color(int R, int G, int B);
int		correct_line(char *txt);
void		fast_exit(char *str, int i);

#endif
