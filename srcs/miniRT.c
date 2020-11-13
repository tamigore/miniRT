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
	(*env)->obj = NULL;
	(*env)->ray = NULL;
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
	if (!(env->ray = init_ray(env->cam->ori, env->cam->dir, 0)))
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

void	reset_sph(t_sph **sph)
{
	if (*sph)
		while ((*sph)->prev)
			(*sph) = (*sph)->prev;
}
