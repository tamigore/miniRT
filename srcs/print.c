/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:17:14 by tamigore          #+#    #+#             */
/*   Updated: 2022/04/06 14:05:00 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_env(t_env *env)
{
	printf("res :%d.x/%d.y\n", env->res.x, env->res.y);
	printf("amb :%.0f.R/%.0f.G/%.0f.B // %.2f.ratio\n", env->amb.color.x,
			env->amb.color.y, env->amb.color.z, env->amb.ratio);
	print_cam(env->cam);
	print_lgt(env->lgt);
	print_obj(env->obj);
}

void		print_cam(t_cam *cam)
{
	t_cam	*tmp;

	if (cam)
	{
		tmp = cam;
		while (tmp)
		{
			printf("cam :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz //%d.fov\n", tmp->pos.x, tmp->pos.y,
			tmp->pos.z, tmp->dir.x, tmp->dir.y, tmp->dir.z, tmp->fov);
			tmp = tmp->next;
		}
	}
	else
		printf("cam :NULL\n");
}

void		print_lgt(t_lgt *lgt)
{
	t_lgt	*tmp;

	if (lgt)
	{
		tmp = lgt;
		while (tmp)
		{
			printf("lgt :%.2f.x/%.2f.y/%.2f.z // %f.ratio // %.0f.R/%.0f.G/%.0f.B\n", tmp->pos.x, tmp->pos.y,
			tmp->pos.z, tmp->ratio, tmp->color.x, tmp->color.y, tmp->color.z);
			tmp = tmp->next;
		}
	}
	else
		printf("lgt :NULL\n");
}

void		print_cyl(t_cyl *cyl)
{
	printf("cyl :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %.0f.R/%.0f.G/%.0f.B // %.2f.h/%.2f.d\n", cyl->pos.x, cyl->pos.y,
			cyl->pos.z, cyl->dir.x, cyl->dir.y, cyl->dir.z, cyl->color.x,
			cyl->color.y, cyl->color.z, cyl->h, cyl->r);
}

void		print_sqr(t_sqr *sqr)
{
	printf("sqr :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %.0f.R/%.0f.G/%.0f.B // %.2f.h\n", sqr->pos.x, sqr->pos.y,
			sqr->pos.z, sqr->dir.x, sqr->dir.y, sqr->dir.z, sqr->color.x,
			sqr->color.y, sqr->color.z, sqr->side);
}

void		print_tri(t_tri *tri)
{
	printf("tri :%.2f.x1/%.2f.y1/%.2f.z1 // %.2f.x2/%.2f.y2/%.2f.z2 // %.2f.x3/%.2f.y3/%.2f.z3 // %.0f.R/%.0f.G/%.0f.B\n", tri->p1.x,
			tri->p1.y, tri->p1.z, tri->p2.x, tri->p2.y, tri->p2.z, tri->p3.z,
			tri->p3.y, tri->p3.z, tri->color.x, tri->color.y, tri->color.z);
}

void		print_pla(t_pla *pla)
{
	printf("pla :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %.0f.R/%.0f.G/%.0f.B\n", pla->pos.x, pla->pos.y, pla->pos.z,
			pla->dir.x, pla->dir.y, pla->dir.z, pla->color.x, pla->color.y,
			pla->color.z);
}

void		print_sph(t_sph *sph)
{
	printf("sph :%.2f.x/%.2f.y/%.2f.z // %.2f.d // %.0f.R/%.0f.G/%.0f.B\n",
			sph->pos.x, sph->pos.y, sph->pos.z, sph->r, sph->color.x,
			sph->color.y, sph->color.z);
}

void		print_ray(t_ray *ray)
{
	if (ray)
	{
		printf("ray :%.2f.x/%.2f.y/%.2f.z//%.2f.vx/%.2f.vy/%.2f.vz//t=%f\n",
		ray->pos.x, ray->pos.y, ray->pos.z, ray->dir.x,
		ray->dir.y, ray->dir.z, ray->t);
	}
	else
		printf("ray :NULL\n");
}

void		print_obj(t_obj *obj)
{
	t_obj	*tmp;

	if (obj)
	{
		tmp = obj;
		while (tmp)
		{
			if (tmp->id == SQUARE)
				print_sqr(tmp->data);
			else if (tmp->id == SPHERE)
				print_sph(tmp->data);
			else if (tmp->id == CYLINDER)
				print_cyl(tmp->data);
			else if (tmp->id == TRIANGLE)
				print_tri(tmp->data);
			else if (tmp->id == PLANE)
				print_pla(tmp->data);
			tmp = tmp->next;
		}
	}
	else
		printf("obj :NULL\n");
}
