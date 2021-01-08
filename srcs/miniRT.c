/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:28:29 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/08 11:14:26 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		main(int ac, char **av)
{
	t_env	*env;
	int		save;

	if (ac < 2 || ac > 3)
		return (0);
	if (ac == 3 && !ft_strcmp(av[2], "--save"))
		save = 1;
	else
		save = 0;
	printf("arg : %s\n", av[1]);
	if (!(env = init_env(av[1], save)))
		return (FAIL);
	print_env(env);
	if (!(mlx_creat_all(env)))
		return (FAIL);
	return (WIN);
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
	(*env)->obj = NULL;
	(*env)->ray = NULL;
}

t_env	*init_env(char *av, int save)
{
	t_env	*env;
	char	*txt;
	int		r;
	int		fd;

	if ((fd = open(av, O_RDONLY)) == -1)
		return (NULL);
	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	zero_env(&env);
	env->save = save;
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
	if (!(env->ray = init_ray(env->cam->pos, env->cam->dir, 0)))
		return (NULL);
	if (!(env->obj = object(env)))
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
