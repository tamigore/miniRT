/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:04:48 by tamigore          #+#    #+#             */
/*   Updated: 2022/05/06 16:57:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_sucess(t_env *env)
{
	free_env(env);
	ft_putstr("EXIT\n");
	exit(END);
}

void	exit_error(t_env *env, char *str)
{
	free_env(env);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
