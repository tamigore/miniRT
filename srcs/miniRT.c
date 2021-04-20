/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:28:29 by tamigore          #+#    #+#             */
/*   Updated: 2021/04/20 12:06:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	usage(void)
{
	ft_putstr("Usage: minirt (--save) <scene.rt>\n");
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac < 2 || ac > 3 || (ac == 3 && ft_strcmp(av[2], "--save")))
		usage();
	printf("arg : %s\n", av[1]);
	env = init_env(ac, av);
	pars_sceen(av, env);
	print_env(env);
	render(env);
	graphic_loop(env);
	return (WIN);
}
