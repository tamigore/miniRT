/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:45:12 by tamigore          #+#    #+#             */
/*   Updated: 2021/01/05 16:19:04 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


static void	write_bmpdata(t_env *env, int fd)
{
}

static void	write_bmpheader(t_env *env, int fd)
{
}

void		set_save(t_env *env, const char *file)
{
	int		fd;

	if (!(fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERM)))
		fast_exit("fd abort", FAIL);
	write_bmpheader(env, fd);
	write_bmpdata(env, fd);
	close(fd);
	fast_exit("success", WIN);
}
