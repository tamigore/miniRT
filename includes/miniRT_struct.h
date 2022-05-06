/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:20:38 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 19:32:30 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "libmath.h"

/*
** t_amb = struct for amb
**
** check = checks whether ambient light is declared and not duplicated
** ratio = ambient lighting ratio in range [0.0,1.0]
** color = R,G,B colors in range [0.0,1.0]
*/

typedef struct s_amb
{
	int				check;
	t_vec			color;
	double			ratio;
}					t_amb;

/*
** t_res = struct for resolution
**
** check : checks if resolution is declared and not duplicated
** size_x: width of the image
** size_y: height of the image
*/

typedef struct s_res
{
	int				check;
	int				x;
	int				y;
}					t_res;

/*
** Image
**
** size_x = width of the image
** size_y = height of the image
** img_ptr = pointer returned by the mlx_new_image() function
** pixels = pointer to image data returned by the mlx_get_data_addr() function
** The 3 following values are obtained using mlx_get_data_addr()
** bpp = bits per pixels
** size_line = the size (char) of a line
** endian = endian type (big : 1 / small : 0)
** next = pointer to next image
*/

typedef struct s_img
{
	int				size_x;
	int				size_y;
	void			*ptr;
	char			*pixels;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

/*
** t_cam = struct for camera
**
** pos = coordinates of the light point for {x, y, z} axis
** dir = 3D-normalized orientation vector in range [-1,1] for {x, y, z} axis
** fov = horizontal field of viewif (root1 > EPSILON && inside_cyl(cyl, ray,
** root1)) in degrees in range [0,180]
** c2w = camera space to world space 3D matrix
** next: pointer to next camera
*/

typedef struct s_cam
{
	t_vec			pos;
	t_vec			dir;
	int				fov;
	t_vec			right;
	t_vec			up;
	t_mat			c2w;
	t_mat			w2c;
	t_mat			rota;
	t_mat			trans;
	struct s_img	img;
	struct s_cam	*next;
}					t_cam;

/*
** t_lum = struct for lights
**
** pos: x,y,z coordinates of the view point
** ratio: Light brightness ratio in range [0.0,1.0]
** color: color of the light in 3 vector R->G->B in range [0.0,1.0]
** next: Pointer to next light
*/

typedef struct s_lgt
{
	t_vec			pos;
	double			ratio;
	t_vec			color;
	struct s_lgt	*next;
}					t_lgt;

/*
** t_pla = struct for planes
**
** pos = coordinates of the plane for {x,y,z} axis
** dir = 3D-normalized orientation vector in range [-1,1] for {x,y,z} axis
** color = color of the plane in 3 vector R->G->B in range [0.0,1.0]
*/

typedef struct s_pla
{
	t_vec			pos;
	t_vec			dir;
	t_vec			color;
}					t_pla;

/*
** t_cyl = struct for cylinders
**
** pos = coordinates of the cylinder bottom for {x,y,z} axis
** dir = 3D-normalized orientation vector in range [-1,1] for {x,y,z} axis
** d = the cylinder diameter
** h = the cylinder height
** color = color of the cylinder in 3 vector R->G->B in range [0.0,1.0]
*/

typedef struct s_cyl
{
	t_vec			pos;
	t_vec			dir;
	double			h;
	double			r;
	t_vec			color;
}					t_cyl;

/*
** t_tri = struct for triangles
**
** p1 = inital position in 3d space {x,y,z} of the first point
** p2 = inital position in 3d space {x,y,z} of the second point
** p3 = inital position in 3d space {x,y,z} of the third point
** color = color of the triangle in 3 vector R->G->B in range [0.0,1.0]
*/

typedef struct s_tri
{
	t_vec			p1;
	t_vec			p2;
	t_vec			p3;
	t_vec			color;
}					t_tri;

/*
** t_sph = struct for spheres
**
** pos = inital position in 3d space {x,y,z}
** r = the sphere radius
** color = color of the sphere in 3 vector R->G->B in range [0.0,1.0]
*/

typedef struct s_sph
{
	t_vec			pos;
	double			r;
	t_vec			color;
}					t_sph;

/*
** t_objid = enum for all object
*/

typedef enum s_objid
{
	SPHERE,
	TRIANGLE,
	CYLINDER,
	PLANE
}					t_objid;

/*
** t_obj = struct for object
**
** id = type of object
** data = strcut of the object with all the data inside
** next = ptr for the next obj in the list
*/

typedef struct s_obj
{
	t_objid			id;
	void			*data;
	t_vec			pos;
	t_vec			dir;
	t_vec			up;
	t_vec			right;
	t_mat			obj2world;
	t_mat			world2obj;
	struct s_obj	*next;
}					t_obj;

/*
** t_ray = struct for rays
**
** pos = inital position in 3d space {x, y, z}
** dir = direction of the ray in 3d space {x, y, z}
** t = distance along the direction from the initial point
** color = color of the ray in 3 vector R->G->B in range [0.0,1.0]
** hit = hit point
** normal at hit point
*/

typedef struct s_ray
{
	t_vec			pos;
	t_vec			dir;
	double			t;
	t_vec			color;
	t_vec			hit;
	t_vec			normal;
}					t_ray;

/*
** t_env = main struct
**
** sceen = contain the data from the sceen file
** mlx = mlx pointer returned by mlx_init()
** win = mlx pointer to the window screne
** res = resolution (width and height) of the window
** amb = ambient light parameters
** nb_cam = number of cameras in the scene
** cam = cameras in the scene
** nb_lgt = number of lights in the scene
** lgt = point lights in the scene
** nb_obj = number of objects in the scene
** obj = objects in the scene
** ray = ray trace throught the scene
** img = rendered images
*/

typedef struct s_env
{
	char			*sceen;
	void			*mlx;
	void			*win;
	struct s_res	res;
	struct s_amb	amb;
	int				nb_cam;
	struct s_cam	*cam;
	int				nb_lgt;
	struct s_lgt	*lgt;
	int				nb_obj;
	struct s_obj	*obj;
	struct s_obj	*hit_obj;
}					t_env;

#endif
