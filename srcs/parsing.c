/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:36:40 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/10 14:32:13 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void		pars(char *txt, t_env **env)
{
	if (txt[0] == 'R' && txt[1] == ' ')
		(*env)->res = resolution(txt);
	else if (txt[0] == 'A' && txt[1] == ' ')
		(*env)->amb = ambiance(txt);
	else if (txt[0] == 'c' && txt[1] == ' ')
	{
		if ((*env)->cam)
		{
			if (!((*env)->cam->next = camera(txt)))
				fast_exit("Error n: camera", FAILURE);
			(*env)->cam->next->prev = (*env)->cam;
			(*env)->cam = (*env)->cam->next;
		}
		else
			if (!((*env)->cam = camera(txt)))
				fast_exit("Error n: camera", FAILURE);
	}
	else if (txt[0] == 'l' && txt[1] == ' ')
	{
		if ((*env)->lum)
		{
			if (!((*env)->lum->next = lumiere(txt)))
				fast_exit("Error n: lumiere", FAILURE);
			(*env)->lum->next->prev = (*env)->lum;
			(*env)->lum = (*env)->lum->next;
		}
		else
			if (!((*env)->lum = lumiere(txt)))
				fast_exit("Error n: lumiere", FAILURE);
	}
	else if (txt[0] == 'c' && txt[1] == 'y' && txt[2] == ' ')
	{
		if ((*env)->cyl)
		{
			if (!((*env)->cyl->next = cylindre(txt)))
				fast_exit("Error n: cylindre", FAILURE);
			(*env)->cyl->next->prev = (*env)->cyl;
			(*env)->cyl = (*env)->cyl->next;
		}
		else
			if (!((*env)->cyl = cylindre(txt)))
				fast_exit("Error n: cylindre", FAILURE);
	}
	else if (txt[0] == 't' && txt[1] == 'r' && txt[2] == ' ')
	{
		if ((*env)->tri)
		{
			if (!((*env)->tri->next = triangle(txt)))
				fast_exit("Error n: triangle", FAILURE);
			(*env)->tri->next->prev = (*env)->tri;
			(*env)->tri = (*env)->tri->next;
		}
		else
			if (!((*env)->tri = triangle(txt)))
				fast_exit("Error n: triangle", FAILURE);
	}
	else if (txt[0] == 's' && txt[1] == 'q' && txt[2] == ' ')
	{
		if ((*env)->car)
		{
			if (!((*env)->car->next = carre(txt)))
				fast_exit("Error n: carre", FAILURE);
			(*env)->car->next->prev = (*env)->car;
			(*env)->car = (*env)->car->next;
		}
		else
			if (!((*env)->car = carre(txt)))
				fast_exit("Error n: carre", FAILURE);
	}
	else if (txt[0] == 'p' && txt[1] == 'l' && txt[2] == ' ')
	{
		if ((*env)->pla)
		{
			if (!((*env)->pla->next = plane(txt)))
				fast_exit("Error n: plane", FAILURE);
			(*env)->pla->next->prev = (*env)->pla;
			(*env)->pla = (*env)->pla->next;
		}
		else
			if (!((*env)->pla = plane(txt)))
				fast_exit("Error n: plane", FAILURE);
	}
	else if (txt[0] == 's' && txt[1] == 'p' && txt[2] == ' ')
	{
		if ((*env)->sph)
		{
			if (!((*env)->sph->next = sphere(txt)))
				fast_exit("Error n: sphere", FAILURE);
			(*env)->sph->next->prev = (*env)->sph;
			(*env)->sph = (*env)->sph->next;
		}
		else
			if (!((*env)->sph = sphere(txt)))
				fast_exit("Error n: sphere", FAILURE);
	}
	else
		fast_exit("Error n: scenes", FAILURE);
}

t_res		*resolution(char *txt)
{
	t_res	*res;
	int		i;

	if (!(res = malloc(sizeof(t_res))))
		return (NULL);
	i = 0;
	res->x = str_to_long(txt, &i);
	res->y = str_to_long(txt, &i);
	if (res->y > DISPLAY_Y)
		res->y = DISPLAY_Y;
	if (res->x > DISPLAY_X)
		res->x = DISPLAY_X;
	if (res->x < 0 || res->y < 0)
	{
		free(res);
		perror("Error n: resolution");
		exit(FAILURE);
	}
	return (res);
}

t_amb		*ambiance(char *txt)
{
	t_amb	*amb;
	int		i;

	if (!(amb = malloc(sizeof(t_amb))))
		return (NULL);
	i = 0;
	amb->l = str_to_double(txt, &i);
	amb->R = str_to_long(txt, &i);
	amb->G = str_to_long(txt, &i);
	amb->B = str_to_long(txt, &i);
	amb->color = rgb2color(amb->R, amb->G, amb->B);
	if (amb->R > 255 || amb->G > 255 || amb->B > 255 || amb->l > 1 ||
		amb->R < 0 || amb->G < 0 || amb->B < 0 || amb->l < 0)
	{
		free(amb);
		perror("Error n: ambiance");
		exit(FAILURE);
	}
	return (amb);
}

t_cam		*camera(char *txt)
{
	t_cam	*cam;
	int		i;

	if (!(cam = malloc(sizeof(t_cam))))
		return (NULL);
	i = 0;
	cam->x = str_to_double(txt, &i);
	cam->y = str_to_double(txt, &i);
	cam->z = str_to_double(txt, &i);
	cam->vx = str_to_double(txt, &i);
	cam->vy = str_to_double(txt, &i);
	cam->vz = str_to_double(txt, &i);
	cam->fov = str_to_long(txt, &i);
	cam->mat = matrix44_init();
	cam->next = NULL;
	cam->prev = NULL;
	if (cam->vx > 1 || cam->vy > 1 || cam->vz > 1 || cam->fov > 180 ||
		cam->vx < -1 || cam->vy < -1 || cam->vz < -1 || cam->fov < 0 || !cam->mat)
	{
		free(cam);
		perror("Error n: camera");
		exit(FAILURE);
	}
	return (cam);
}

t_lum		*lumiere(char *txt)
{
	t_lum	*lum;
	int		i;

	if (!(lum = malloc(sizeof(t_lum))))
		return (NULL);
	i = 0;
	lum->x = str_to_double(txt, &i);
	lum->y = str_to_double(txt, &i);
	lum->z = str_to_double(txt, &i);
	lum->l = str_to_double(txt, &i);
	lum->R = str_to_long(txt, &i);
	lum->G = str_to_long(txt, &i);
	lum->B = str_to_long(txt, &i);
	lum->color = rgb2color(lum->R, lum->G, lum->B);
	lum->next = NULL;
	lum->prev = NULL;
	if (lum->R > 255 || lum->G > 255 || lum->B > 255 || lum->l > 1 ||
		lum->R < 0 || lum->G < 0 || lum->B < 0 || lum->l < 0)
	{
		free(lum);
		perror("Error n: lumiere");
		exit(FAILURE);
	}
	return (lum);
}

t_cyl		*cylindre(char *txt)
{
	t_cyl	*cyl;
	int		i;

	if (!(cyl = malloc(sizeof(t_cyl))))
		return (NULL);
	i = 0;
	cyl->x = str_to_double(txt, &i);
	cyl->y = str_to_double(txt, &i);
	cyl->z = str_to_double(txt, &i);
	cyl->vx = str_to_double(txt, &i);
	cyl->vy = str_to_double(txt, &i);
	cyl->vz = str_to_double(txt, &i);
	cyl->R = str_to_long(txt, &i);
	cyl->G = str_to_long(txt, &i);
	cyl->B = str_to_long(txt, &i);
	cyl->color = rgb2color(cyl->R, cyl->G, cyl->B);
	cyl->h = str_to_double(txt, &i);
	cyl->d = str_to_double(txt, &i);
	cyl->next = NULL;
	cyl->prev = NULL;
	if (cyl->vx > 1 || cyl->vy > 1 || cyl->vz > 1 || cyl->R > 255 ||
		cyl->vx < -1 || cyl->vy < -1 || cyl->vz < -1 || cyl->R < 0 ||
		cyl->G > 255 || cyl->B > 255 || cyl->G < 0 || cyl->B < 0)
	{
		free(cyl);
		perror("Error n: cylindre");
		exit(FAILURE);
	}
	return (cyl);
}

t_tri		*triangle(char *txt)
{
	t_tri	*tri;
	int		i;

	if (!(tri = malloc(sizeof(t_tri))))
		return (NULL);
	i = 0;
	tri->x1 = str_to_double(txt, &i);
	tri->y1 = str_to_double(txt, &i);
	tri->z1 = str_to_double(txt, &i);
	tri->x2 = str_to_double(txt, &i);
	tri->y2 = str_to_double(txt, &i);
	tri->z2 = str_to_double(txt, &i);
	tri->x3 = str_to_double(txt, &i);
	tri->y3 = str_to_double(txt, &i);
	tri->z3 = str_to_double(txt, &i);
	tri->R = str_to_long(txt, &i);
	tri->G = str_to_long(txt, &i);
	tri->B = str_to_long(txt, &i);
	tri->color = rgb2color(tri->R, tri->G, tri->B);
	tri->next = NULL;
	tri->prev = NULL;
	if (tri->R > 255 || tri->R < 0 || tri->G > 255 ||
		tri->B > 255 || tri->G < 0 || tri->B < 0)
	{
		free(tri);
		perror("Error n: triangle");
		exit(FAILURE);
	}
	return (tri);
}

t_car		*carre(char *txt)
{
	t_car	*car;
	int		i;

	if (!(car = malloc(sizeof(t_car))))
		return (NULL);
	i = 0;
	car->x = str_to_double(txt, &i);
	car->y = str_to_double(txt, &i);
	car->z = str_to_double(txt, &i);
	car->vx = str_to_double(txt, &i);
	car->vy = str_to_double(txt, &i);
	car->vz = str_to_double(txt, &i);
	car->h = str_to_double(txt, &i);
	car->R = str_to_long(txt, &i);
	car->G = str_to_long(txt, &i);
	car->B = str_to_long(txt, &i);
	car->color = rgb2color(car->R, car->G, car->B);
	car->next = NULL;
	car->prev = NULL;
	if (car->vx > 1 || car->vy > 1 || car->vz > 1 || car->R > 255 ||
		car->vx < -1 || car->vy < -1 || car->vz < -1 || car->R < 0 ||
		car->G > 255 || car->B > 255 || car->G < 0 || car->B < 0)
	{
		free(car);
		perror("Error n: carre");
		exit(FAILURE);
	}
	return (car);
}

t_pla		*plane(char *txt)
{
	t_pla	*pla;
	int		i;

	if (!(pla = malloc(sizeof(t_pla))))
		return (NULL);
	i = 0;
	pla->x = str_to_double(txt, &i);
	pla->y = str_to_double(txt, &i);
	pla->z = str_to_double(txt, &i);
	pla->vx = str_to_double(txt, &i);
	pla->vy = str_to_double(txt, &i);
	pla->vz = str_to_double(txt, &i);
	pla->R = str_to_long(txt, &i);
	pla->G = str_to_long(txt, &i);
	pla->B = str_to_long(txt, &i);
	pla->color = rgb2color(pla->R, pla->G, pla->B);
	pla->next = NULL;
	pla->prev = NULL;
	if (pla->vx > 1 || pla->vy > 1 || pla->vz > 1 || pla->R > 255 ||
		pla->vx < -1 || pla->vy < -1 || pla->vz < -1 || pla->R < 0 ||
		pla->G > 255 || pla->B > 255 || pla->G < 0 || pla->B < 0)
	{
		free(pla);
		perror("Error n: plane");
		exit(FAILURE);
	}
	return (pla);
}

t_sph		*sphere(char *txt)
{
	t_sph	*sph;
	int		i;

	if (!(sph = malloc(sizeof(t_sph))))
		return (NULL);
	i = 0;
	sph->x = str_to_double(txt, &i);
	sph->y = str_to_double(txt, &i);
	sph->z = str_to_double(txt, &i);
	sph->d = str_to_double(txt, &i);
	sph->r = sph->d / 2;
	sph->R = str_to_long(txt, &i);
	sph->G = str_to_long(txt, &i);
	sph->B = str_to_long(txt, &i);
	sph->color = rgb2color(sph->R, sph->G, sph->B);
	sph->next = NULL;
	sph->prev = NULL;
	if (sph->R > 255 || sph->R < 0 || sph->G > 255 || sph->B > 255 ||
		sph->G < 0 || sph->B < 0)
	{
		free(sph);
		perror("Error n: sphere");
		exit(FAILURE);
	}
	return (sph);
}

t_obj		*object()
{
	t_obj	*obj;

	if (!(obj = malloc(sizeof(t_obj))))
		return (NULL);
	obj->nb = 0;
	obj->dist = 0;
	obj->color = 0;
	obj->car = NULL;
	obj->pla = NULL;
	obj->tri = NULL;
	obj->cyl = NULL;
	obj->sph = NULL;
	return (obj);
}
