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
#include <stdarg.h>

#define DISPLAY_X 1200	//2560
#define DISPLAY_Y 800	//1440
#define FAILURE -1
#define SUCCESS 1
#define END 0
#define MAX_DEPH 1000000000

typedef struct		s_cam
{
	t_v3			ori;
	int				fov;
	t_v3			dir;
	double			**mat;
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
	t_v3			ori;
	double			l;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_lum	*next;
	struct s_lum	*prev;
}					t_lum;

typedef struct		s_amb
{
	int				R;
	int				G;
	int				B;
	int				color;
	double			l;
}					t_amb;

typedef struct		s_pla
{
	t_v3			ori;
	t_v3			dir;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_pla	*next;
	struct s_pla	*prev;
}					t_pla;

typedef struct		s_car
{
	t_v3			ori;
	double			h;
	t_v3			dir;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_car	*next;
	struct s_car	*prev;
}					t_car;

typedef struct		s_cyl
{
	t_v3			ori;
	double			h;
	double			d;
	t_v3			dir;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_cyl	*next;
	struct s_cyl	*prev;
}					t_cyl;

typedef struct		s_tri
{
	t_v3			p1;
	t_v3			p2;
	t_v3			p3;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_tri	*next;
	struct s_tri	*prev;
}					t_tri;

typedef struct		s_sph
{
	t_v3			ori;
	double			d;
	double			r;
	int				R;
	int				G;
	int				B;
	int				color;
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

typedef struct		s_obj
{
	int				nb;
	double			dist;
	int				color;
	struct s_car	*car;
	struct s_pla	*pla;
	struct s_tri	*tri;
	struct s_cyl	*cyl;
	struct s_sph	*sph;
}					t_obj;

typedef struct		s_ray
{
	t_v3			ori;
	t_v3			dir;
	double			t;
}					t_ray;

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
	struct s_obj	*obj;
	struct s_ray	*ray;
}					t_env;

/*
** miniRT.c
*/

t_env		*init_env(char *av);
void		pars(char *txt, t_env **env);
void 		reset_env(t_env **env);
void		reset_sph(t_sph **sph);

/*
** print.c
*/

void		print_env(t_env *env);
void		print_cam(t_cam *cam);
void		print_lum(t_lum *lum);
void		print_cyl(t_cyl *cyl);
void		print_car(t_car *car);
void		print_tri(t_tri *tri);
void		print_pla(t_pla *pla);
void		print_sph(t_sph *sph);
void		print_ray(t_ray *ray);
void		print_obj(t_obj *obj);

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

int			mlx_creat_all(t_env **env);
int			win_pixel(t_env *env);
t_v3		canvas2view(t_env *env, int x, int y);
t_v3		vector_direct(int fov, int resX, int resY, int x, int y);

/*
** tarce.c
*/

int			trace(t_env *env);
int			trace_sph(t_env *env);
int			trace_ray(t_env *env, t_ray *ray);

/*
** intersect.c
*/

int			count_obj(t_env *env);
int			SolveQuadratic(float a, float b, float c, float *x0, float *x1);
int			sphere_intersect(t_sph *sph, t_ray *ray);

/*
** utils.c
*/

int			rgb2color(int R, int G, int B);
int			correct_line(char *txt);
void		fast_exit(char *str, int i);
double		MaxVal(int nb, ...);
void		swap(double *x, double *y);

/*
** matrix.c
*/

double		**lookAt(double **cam2world, t_v3 to, t_v3 from, t_v3 pos);
double		**matrix44_init();
void		matrix_row(double a, double b, double c, double d, double *M);
t_v3		vec3Xmat4(t_v3 vec, double **M);

/*
** ray.c
*/

t_ray		*init_ray();
void		ft_ray(t_ray *ray, t_v3 ori, t_v3 dir, double t);

/*
** obj.c
*/

t_obj		*object();
int			count_obj(t_env *env);
void		get_color(t_obj *obj);
void		reset_obj(t_obj *obj);
void		obj_sph(t_env *env, t_obj *obj);

#endif
