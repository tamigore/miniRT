/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:28:29 by tamigore          #+#    #+#             */
/*   Updated: 2020/03/02 20:43:52 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int		main(int ac, char **av)
{
	t_env	*env;
	void	*ptr;

	if (ac < 2)
		return (0);
	printf("arg : %s\n", av[1]);
	if (!(env = init_env(av[1])))
		return (FAILURE);
	if (!(ptr = mlx_init()))
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
	print_env(env);
	return (env);
}

void	print_env(t_env *env)
{
	if (env->res)
		printf("res :%d.x/%d.y\n", env->res->x, env->res->y);
	if (env->amb)
		printf("amb :%d.R/%d.G/%d.B // %.2f.l\n", env->amb->R, env->amb->G,
		env->amb->B, env->amb->l);
	if (env->cam)
		printf("cam :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz //%d.fov\n", env->cam->x, env->cam->y,
		env->cam->z, env->cam->vx, env->cam->vy, env->cam->vz, env->cam->fov);
	if (env->lum)
		printf("lum :%.2f.x/%.2f.y/%.2f.z // %f.l // %d.R/%d.G/%d.B\n", env->lum->x, env->lum->y,
		env->lum->z, env->lum->l, env->lum->R, env->lum->G, env->lum->B);
	if (env->cyl)
		printf("cyl :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B // %.2f.h/%.2f.d\n", env->cyl->x, env->cyl->y,
		env->cyl->z, env->cyl->vx, env->cyl->vy, env->cyl->vz, env->cyl->R, env->cyl->G, env->cyl->B, env->cyl->h, env->cyl->d);
	if (env->car)
		printf("car :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B // %f.h\n", env->car->x, env->car->y,
		env->car->z, env->car->vx, env->car->vy, env->car->vz, env->car->R, env->car->G, env->car->B, env->car->h);
	if (env->tri)
		printf("tri :%.2f.x1/%.2f.y1/%.2f.z1 // %.2f.x2/%.2f.y2/%.2f.z2 // %.2f.x3/%.2f.y3/%.2f.z3 // %d.R/%d.G/%d.B\n", env->tri->x1, env->tri->y1, env->tri->z1,
		env->tri->x2, env->tri->y2, env->tri->z2, env->tri->x3, env->tri->y3, env->tri->z3, env->tri->R, env->tri->G, env->tri->B);
	if (env->pla)
		printf("pla :%.2f.x/%.2f.y/%.2f.z // %.2f.vx/%.2f.vy/%.2f.vz // %d.R/%d.G/%d.B\n", env->pla->x, env->pla->y,
		env->pla->z, env->pla->vx, env->pla->vy, env->pla->vz, env->pla->R, env->pla->G, env->pla->B);
	if (env->sph)
		printf("sph :%.2f.x/%.2f.y/%.2f.z // %.2f.d // %d.R/%d.G/%d.B\n", env->sph->x, env->sph->y,
		env->sph->z, env->sph->d, env->sph->R, env->sph->G, env->sph->B);
}

int		correct_line(char *txt)
{
	if (!ft_strncmp(txt, "R ", 2) || !ft_strncmp(txt, "A ", 2) ||
		!ft_strncmp(txt, "l ", 2) || !ft_strncmp(txt, "c ", 2) ||
		!ft_strncmp(txt, "tr ", 3) || !ft_strncmp(txt, "cy ", 3) ||
		!ft_strncmp(txt, "sq ", 3) || !ft_strncmp(txt, "sp ", 3))
		return (1);
	return (0);
}
