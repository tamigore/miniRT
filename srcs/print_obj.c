/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:06:09 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 18:23:46 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_obj(t_obj *obj)
{
	t_obj	*tmp;

	if (obj)
	{
		tmp = obj;
		while (tmp)
		{
			if (tmp->id == SPHERE)
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

void	print_cyl(t_cyl *cyl)
{
	printf("cyl :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // \
		%.0f.R/%.0f.G/%.0f.B // %.2f.h/%.2f.r\n", cyl->pos.x, cyl->pos.y,
		cyl->pos.z, cyl->dir.x, cyl->dir.y, cyl->dir.z, cyl->color.x,
		cyl->color.y, cyl->color.z, cyl->h, cyl->r);
}

void	print_tri(t_tri *tri)
{
	printf("tri :%.2f.x1/%.2f.y1/%.2f.z1 // %.2f.x2/%.2f.y2/%.2f.z2 // \
		%.2f.x3/%.2f.y3/%.2f.z3 // %.0f.R/%.0f.G/%.0f.B\n", tri->p1.x,
		tri->p1.y, tri->p1.z, tri->p2.x, tri->p2.y, tri->p2.z, tri->p3.z,
		tri->p3.y, tri->p3.z, tri->color.x, tri->color.y, tri->color.z);
}

void	print_pla(t_pla *pla)
{
	printf("pla :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // \
		%.0f.R/%.0f.G/%.0f.B\n", pla->pos.x, pla->pos.y, pla->pos.z,
		pla->dir.x, pla->dir.y, pla->dir.z, pla->color.x, pla->color.y,
		pla->color.z);
}

void	print_sph(t_sph *sph)
{
	printf("sph :%.2f.x/%.2f.y/%.2f.z // %.2f.r // %.0f.R/%.0f.G/%.0f.B\n",
		sph->pos.x, sph->pos.y, sph->pos.z, sph->r, sph->color.x,
		sph->color.y, sph->color.z);
}
