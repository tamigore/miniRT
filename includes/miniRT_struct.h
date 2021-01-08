/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:20:38 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/07 16:45:28 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_STRUCT_H_
# define _MINIRT_STRUCT_H_

# include "libmath.h"

/*
** structure pour les cameras
*/

typedef struct		s_cam
{
	t_v3			pos;
	int				fov;
	t_v3			dir;
	double			**mat;
	struct s_cam	*next;
	struct s_cam	*prev;
}					t_cam;

/*
** structure pour la resolution
*/

typedef struct		s_res
{
	int				x;
	int				y;
}					t_res;

/*
** structure pour les lumieres
*/

typedef struct		s_lum
{
	t_v3			pos;
	double			l;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_lum	*next;
	struct s_lum	*prev;
}					t_lum;

/*
** strcuture pour l'ambiance
*/

typedef struct		s_amb
{
	int				R;
	int				G;
	int				B;
	int				color;
	double			l;
}					t_amb;

/*
** structure pour les plans
*/

typedef struct		s_pla
{
	t_v3			pos;
	t_v3			dir;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_pla	*next;
	struct s_pla	*prev;
}					t_pla;

/*
** structure pour les carres
*/

typedef struct		s_car
{
	t_v3			pos;
	double			h;
	t_v3			dir;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_car	*next;
	struct s_car	*prev;
}					t_car;

/*
** structure pour les cylindres
*/

typedef struct		s_cyl
{
	t_v3			pos;
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

/*
** structure pour les triangles
*/

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

/*
** structure pour les spheres
*/

typedef struct		s_sph
{
	t_v3			pos;
	double			d;
	double			r;
	int				R;
	int				G;
	int				B;
	int				color;
	struct s_sph	*next;
	struct s_sph	*prev;
}					t_sph;

/*
** structure pour la minilibx
*/

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*ima;
	char			*adr;
}					t_mlx;

/*
** strcuture pour les objects
*/

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

/*
** structure des rayons
*/

typedef struct		s_ray
{
	t_v3			pos;
	t_v3			dir;
	double			t;
	t_v3			color;
	struct s_ray	*next;
	struct s_ray	*prev;
}					t_ray;

/*
** structure principal environement
*/

typedef struct		s_env
{
	int				save;
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

#endif
