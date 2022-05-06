/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:28:29 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 17:05:29 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** usage : secure file
** ATTENTION |.rt|
*/

static int	usage(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '.')
		{
			if (!ft_strcmp(".rt", &str[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

/*
** main : check | pars & initialize | compute ray | graphic interface
*/
int	main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2 || !av || !usage(av[1]))
	{
		ft_putstr_fd("Error: Usage: minirt: ./miniRT <scene.rt>\n", 2);
		exit(0);
	}
	printf("arg : %s\n", av[1]);
	env = init_env();
	pars_sceen(av[1], env);
	if (env->res.check == 0)
	{
		env->res.x = 500;
		env->res.y = 500;
	}
	print_env(env);
	render(env);
	graphic_loop(env);
	return (END);
}
