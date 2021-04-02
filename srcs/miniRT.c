/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:28:29 by tamigore          #+#    #+#             */
/*   Updated: 2021/03/17 09:24:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		put_image_to_window(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
	return (0);
}

static void	switch_cam(t_env *env)
{
	env->img = env->img->next;
	put_image_to_window(env);
}

static int		key_call(int key, void *param)
{
	t_env		*env;

	env = (t_env *)param;
	if (key == ESCAPE)
		exit_sucess(env);
	if (key == SPACE)
		switch_cam(env);
	return (0);
}

static void		display(t_env *env)
{
	put_image_to_window(env);
	ft_putstr("press ESCAPE to close\n");
	mlx_key_hook(env->mlx, key_call, env);
	mlx_hook(env->mlx, DESTROYNOTIFY, 1L << 17, exit_sucess, env);
//	mlx_hook(env->mlx, MAPNOTIFY, 1L << 17, put_image_to_window, env);
	mlx_loop(env->mlx);
}

	int			main(int ac, char **av)
{
	t_env	*env;
	int		save;

	if (ac < 2 || ac > 3)
		return (0);
	save = 0;
	if (ac == 3 && !ft_strcmp(av[2], "--save"))
		save = 1;
	printf("arg : %s\n", av[1]);
	if (!(env = init_env(av[1], save)))
		exit_error(env, ERRNO_TO_STR);
	print_env(env);
	if (!(mlx_creat_all(env)))
		exit_error(env, ERRNO_TO_STR);
	if (!(render(env, save)))
		exit_error(env, ERRNO_TO_STR);
	display(env);
	return (WIN);
}
