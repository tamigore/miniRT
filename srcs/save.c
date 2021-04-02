/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:45:12 by tamigore          #+#    #+#             */
/*   Updated: 2021/02/01 15:53:19 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	creat_fileheader(t_bmfh *file, int size)
{
	ft_bzero(file, sizeof(t_bmfh));
	file->type[0] = 'B';
	file->type[1] = 'M';
	file->size = 54 + size;
	file->reserved1 = 0;
	file->reserved2 = 0;
	file->offset = 54;
}

static void	creat_infoheader(t_env *env, t_bmih *info, int size)
{
	int		ppm;

	ppm = 96 * 39.375;
	ft_bzero(info, sizeof(t_bmih));
	info->size = sizeof(t_bmih);
	info->width = env->res.x;
	info->height = env->res.y;
	info->planes = 1;
	info->bit_count = 24;
	info->compression = 0;
	info->img_size = 54 + size;
	info->ppm_x = ppm;
	info->ppm_y = ppm;
	info->clr_used = 0;
	info->clr_important = 0;
}

static void	write_bmpheader(t_env *env, int fd)
{
	t_bmfh	file;
	t_bmih	info;
	int		size;

	size = env->res.x * env->res.y * 3;
	creat_fileheader(&file, size);
	creat_infoheader(env, &info, size);
	write(fd, &(file.type), 2);
	write(fd, &(file.size), 4);
	write(fd, &(file.reserved1), 2);
	write(fd, &(file.reserved2), 2);
	write(fd, &(file.offset), 4);
	write(fd, &(info.size), 4);
	write(fd, &(info.width), 4);
	write(fd, &(info.height), 4);
	write(fd, &(info.planes), 2);
	write(fd, &(info.bit_count), 2);
	write(fd, &(info.compression), 4);
	write(fd, &(info.img_size), 4);
	write(fd, &(info.ppm_x), 4);
	write(fd, &(info.ppm_y), 4);
	write(fd, &(info.clr_used), 4);
	write(fd, &(info.clr_important), 4);
}

static void	write_bmpdata(t_env *env, int fd)
{
	int		x;
	int		y;
	int		*pixel;
	int		i;

	y = env->res.y - 1;
	while (y > -1)
	{
		x = 0;
		while (x < env->res.x)
		{
			i = (x + env->res.x * y) * 4;
			pixel = (int *)(env->img->pixels + i);
			if (write(fd, pixel, 4) < 0)
				exit_error(env, ERRNO_TO_STR);
			x++;
		}
		y--;
	}
}

void		set_save(t_env *env, const char *file)
{
	int		fd;

	if (!(fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERM)))
		exit_error(env, ERRNO_TO_STR);
	write_bmpheader(env, fd);
	write_bmpdata(env, fd);
	close(fd);
	exit_sucess(env);
}
