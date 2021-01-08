/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:30:18 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/07 16:46:49 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_H_
# define _MINIRT_H_

#include "mlx.h"
#include "libft.h"
#include "libmath.h"
#include "miniRT_struct.h"
#include "miniRT_define.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

/*
** miniRT.c
*/

t_env		*init_env(char *av, int save);
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
** obj.c
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
** Count.c
*/

int			count_pla(t_pla *pla);
int			count_sph(t_sph *sph);
int			count_tri(t_tri *tri);
int			count_cyl(t_cyl *cyl);
int			count_car(t_car *car);

/*
** mlx.c
*/

int			mlx_creat_all(t_env *env);
int			win_pixel(t_env *env);
t_v3		canvas2view(t_env *env, int x, int y);
t_v3		vector_direct(int fov, int resX, int resY, int x, int y);

/*
** tarce.c
*/

int			trace(t_env *env, t_ray *ray);
int			trace_sph(t_env *env, t_ray *ray);
int			trace_pla(t_env *env, t_ray *ray);
int			trace_ray(t_env *env);

/*
** intersect.c
*/

int			count_obj(t_env *env);
int			SolveQuadratic(float a, float b, float c, float *x0, float *x1);
int			sphere_intersect(t_sph *sph, t_ray *ray);
int			plane_intersect(t_env *env, t_ray *ray);

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

double		**lookAt(double **cam2world, t_v3 dir, t_v3 pos);

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
void		obj_sph(t_env *env);
void		obj_pla(t_env *env, t_obj *obj);

#endif
