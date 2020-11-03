/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:28:29 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/11 19:38:20 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		main(int ac, char **av)
{
	t_env	*env;

	if (ac < 2)
		return (0);
	printf("arg : %s\n", av[1]);
	if (!(env = init_env(av[1])))
		return (FAILURE);
	print_env(env);
	if (!(mlx_creat_all(&env)))
		return (FAILURE);
	return (SUCCESS);
}

void	zero_env(t_env **env)
{
	(*env)->cam = NULL;
	(*env)->res = NULL;
	(*env)->lum = NULL;
	(*env)->amb = NULL;
	(*env)->car = NULL;
	(*env)->pla = NULL;
	(*env)->tri = NULL;
	(*env)->cyl = NULL;
	(*env)->sph = NULL;
	(*env)->mlx = NULL;
}

t_env	*init_env(char *av)
{
	t_env	*env;
	char	*txt;
	int		r;
	int		fd;

	if (!av)
		return (NULL);
	fd = open(av, O_RDONLY);
	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	zero_env(&env);
	while ((r = get_next_line(fd, &txt)) >= 0)
	{
		if (correct_line(txt))
		{
			printf("%s\n", txt);
			pars(txt, &env);
		}
		free(txt);
		if (r == 0)
			break;
	}
	if (!(env->mlx = malloc(sizeof(t_mlx *))))
		return (NULL);
	if (!(env->obj = object()))
		return (NULL);
	reset_env(&env);
	close(fd);
	return (env);
}

void 	reset_env(t_env **env)
{
	if ((*env)->cam)
		while ((*env)->cam->prev)
			(*env)->cam = (*env)->cam->prev;
	if ((*env)->lum)
		while ((*env)->lum->prev)
			(*env)->lum = (*env)->lum->prev;
	if ((*env)->cyl)
		while ((*env)->cyl->prev)
			(*env)->cyl = (*env)->cyl->prev;
	if ((*env)->car)
		while ((*env)->car->prev)
			(*env)->car = (*env)->car->prev;
	if ((*env)->tri)
		while ((*env)->tri->prev)
			(*env)->tri = (*env)->tri->prev;
	if ((*env)->pla)
		while ((*env)->pla->prev)
			(*env)->pla = (*env)->pla->prev;
	if ((*env)->sph)
		while ((*env)->sph->prev)
		(*env)->sph = (*env)->sph->prev;
}

void	print_env(t_env *env)
{
	if (env->res)
		printf("res :%d.x/%d.y\n", env->res->x, env->res->y);
	if (env->amb)
		printf("amb :%d.R/%d.G/%d.B // %.2f.l\n", env->amb->R, env->amb->G,
		env->amb->B, env->amb->l);
	while (env->cam)
	{
			printf("cam :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz //%d.fov\n", env->cam->x, env->cam->y,
			env->cam->z, env->cam->vx, env->cam->vy, env->cam->vz, env->cam->fov);
			if (env->cam->next)
				env->cam = env->cam->next;
			else
				break;
	}
	while (env->lum)
	{
		printf("lum :%.2f.x/%.2f.y/%.2f.z // %f.l // %d.R/%d.G/%d.B\n", env->lum->x, env->lum->y,
		env->lum->z, env->lum->l, env->lum->R, env->lum->G, env->lum->B);
		if (env->lum->next)
			env->lum = env->lum->next;
		else
			break;
	}
	while (env->cyl)
	{
		printf("cyl :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B // %.2f.h/%.2f.d\n", env->cyl->x, env->cyl->y,
		env->cyl->z, env->cyl->vx, env->cyl->vy, env->cyl->vz, env->cyl->R, env->cyl->G, env->cyl->B, env->cyl->h, env->cyl->d);
		if (env->cyl->next)
			env->cyl = env->cyl->next;
		else
			break;
	}
	while (env->car)
	{
		printf("car :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B // %.2f.h\n", env->car->x, env->car->y,
		env->car->z, env->car->vx, env->car->vy, env->car->vz, env->car->R, env->car->G, env->car->B, env->car->h);
		if (env->car->next)
			env->car = env->car->next;
		else
			break;
	}
	while (env->tri)
	{
		printf("tri :%.2f.x1/%.2f.y1/%.2f.z1 // %.2f.x2/%.2f.y2/%.2f.z2 // %.2f.x3/%.2f.y3/%.2f.z3 // %d.R/%d.G/%d.B\n", env->tri->x1, env->tri->y1, env->tri->z1,
		env->tri->x2, env->tri->y2, env->tri->z2, env->tri->x3, env->tri->y3, env->tri->z3, env->tri->R, env->tri->G, env->tri->B);
		if (env->tri->next)
			env->tri = env->tri->next;
		else
			break;
	}
	while (env->pla && env->pla->next)
	{
		printf("pla :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B\n", env->pla->x, env->pla->y,
		env->pla->z, env->pla->vx, env->pla->vy, env->pla->vz, env->pla->R, env->pla->G, env->pla->B);
		if (env->pla->next)
			env->pla = env->pla->next;
		else
			break;
	}
	while (env->sph && env->sph->next)
	{
		printf("sph :%.2f.x/%.2f.y/%.2f.z // %.2f.d // %d.R/%d.G/%d.B\n", env->sph->x, env->sph->y,
		env->sph->z, env->sph->d, env->sph->R, env->sph->G, env->sph->B);
		if (env->sph->next)
			env->sph = env->sph->next;
		else
			break;
	}
	printf("obj :%d.nb/%.2f.dist/%d.color\n", env->obj->nb, env->obj->dist, env->obj->color);

}
