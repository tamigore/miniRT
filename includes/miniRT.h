/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:01:45 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 19:02:14 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "libmath.h"
# include "miniRT_struct.h"
# include "miniRT_define.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdio.h>
# include <stdarg.h>

/*
** loop.c
*/

int			close_program(t_env *env);
int			key_handler(int keycode, t_env *env);
void		graphic_loop(t_env *env);

/*
** cam_move.c
*/

void		move_left_right(t_env *env, int keycode);
void		move_forward_backward(t_env *env, int keycode);
void		move_up_down(t_env *env, int keycode);
void		rotate_1(t_env *env, int keycode);
void		rotate_2(t_env *env, int keycode);

/*
** parsing.c
*/

void		pars_sceen(char *av, t_env *env);

/*
** init.c
*/

t_env		*init_env(void);
t_cam		*init_camera(t_env *env);
void		append_cam(t_cam **cams, t_cam *new_cam);
t_lgt		*init_light(t_env *env);
void		append_lgt(t_lgt **lgts, t_lgt *new_lgt);

/*
** print.c
*/

void		print_env(t_env *env);
void		print_cam(t_cam *cam);
void		print_lgt(t_lgt *lum);
void		print_cyl(t_cyl *cyl);
void		print_tri(t_tri *tri);
void		print_pla(t_pla *pla);
void		print_sph(t_sph *sph);
void		print_ray(t_ray *ray);
void		print_obj(t_obj *obj);
void		print_matrix(t_mat mat);

/*
** obj.c
*/

t_obj		*init_object(t_env *env);
void		append_obj(t_obj **objs, t_obj *new_obj);
t_vec		get_obj_color(t_obj *obj);
void		get_obj_normal(t_obj *obj, t_ray *ray);
t_vec		*get_obj_pos(t_obj *obj);
t_vec		*get_obj_dir(t_obj *obj);

/*
** obj_move.c
*/
void		obj_move(int keycode, t_env *env);

/*
** conv_nb.c
*/

double		str_to_double(t_env *env);
double		str_to_long(t_env *env);
double		str_to_unsigned(t_env *env);

/*
** render.c
*/

void		trace_ray(t_env *env);
t_img		init_img(t_env *env);
void		render(t_env *env);

/*
** trace.c
*/

void		put_pixel_to_image(t_img img, t_vec color, int x, int y);
void		shade(t_env *env, t_ray *ray);
void		lights(t_obj *obj, t_ray *ray, t_env *env, t_vec *color);
t_vec		rgbzed(double intens, t_vec obj_color, t_vec lgt_color);
t_vec		v_add_rgb(t_vec a, t_vec b);
t_vec		v_scale_rgb(double x, t_vec a);

/*
** trace_obj.c
*/

int			trace_sph(t_sph *sph, t_ray *ray);
int			trace_pla(t_pla *pla, t_ray *ray);
int			trace_cyl(t_cyl *cyl, t_ray *ray);
int			trace_tri(t_tri *tri, t_ray *ray);

/*
** hit.c
*/

t_obj		*hit_objs(t_obj *obj, t_ray *ray);
int			hit_obj(t_obj *obj, t_ray *ray, double *t);

/*
** intersect.c
*/

int			sphere_intersect(t_sph *sph, t_ray *ray, double *t);
int			plane_intersect(t_pla *pla, t_ray *ray, double *t);
int			triangle_intersect(t_tri *tri, t_ray *ray, double *t);

/*
** intersect.c
*/

int			cylinder_intersect(t_cyl *cyl, t_ray *ray, double *t);
double		inter_cylinder(t_ray *ray, t_cyl *cyl, t_vec *normal);

/*
** inter_util.c
*/

int			solve_quadratic(t_vec coef, double *x0, double *x1);
int			hit_plane(t_vec pos, t_vec dir, t_ray *ray, double *t);
int			check_edge(t_vec to, t_vec from, t_vec hit, t_vec normal);

/*
** utils.c
*/

t_vec		rescale_vec(t_vec vec, int min, int max);
char		*ft_strjoindelone(char *s1, char *s2);
int			rgb2color(int R, int G, int B);
int			check_val(double val, double min, double max);
int			check_vec(t_vec vec, double max, double min);

/*
** look_at.c
*/

t_ray		canvas2view(t_env *env, t_cam *cam, int x, int y);

/*
** ray.c
*/

void		reset_ray(t_ray *ray);
void		set_ray(t_ray *ray, t_vec pos, t_vec dir, double t);
void		init_ray(t_ray *ray);

/*
** get_scene.c
*/

void		get_camera(t_env *env);
void		get_light(t_env *env);
void		get_resolution(t_env *env);
void		get_ambient(t_env *env);

/*
** get_obj.c
*/

void		get_sphere(t_env *env);
void		get_plane(t_env *env);
void		get_cylinder(t_env *env);
void		get_triangle(t_env *env);

/*
** get_plus.c
*/

void		get_spher_plus(t_env *env, t_obj *obj);
void		get_plane_plus(t_env *env, t_obj *obj);
void		get_cyliner_plus(t_env *env, t_obj *obj);
void		get_triangle_plus(t_env *env, t_obj *obj);

/*
** get_normal.c
*/

t_vec		get_sph_normal(t_sph *sph, t_ray *ray);
t_vec		get_cyl_normal(t_cyl *cyl, t_ray *ray);
t_vec		get_tri_normal(t_tri *tri);

/*
** free.c
*/

void		free_env(t_env *env);

/*
** exit.c
*/

void		exit_error(t_env *env, char *str);
void		exit_sucess(t_env *env);

/*
** world_coord.c
*/

void		set_mat_cam(t_cam *cam, t_vec rotation);
void		set_mat_obj(t_obj *obj, t_vec rotation);
t_mat		world2obj_mat(t_vec dir, t_vec up, t_vec right);
t_mat		obj2world_mat(t_mat w2c);
t_vec		get_orthogonal(t_vec vec);

#endif
