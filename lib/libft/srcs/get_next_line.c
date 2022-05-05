/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:14:16 by tamigore          #+#    #+#             */
/*   Updated: 2019/11/22 17:18:20 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_lst	*ft_f(t_lst **f, int fd)
{
	t_lst	*tmp;

	tmp = *f;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = (t_lst *)malloc(sizeof(t_lst));
	if (!tmp)
		return (NULL);
	tmp->content = ft_strnew(1);
	if (!tmp->content)
		return (NULL);
	tmp->fd = fd;
	tmp->next = *f;
	*f = tmp;
	return (tmp);
}

static int	ft_strcncat(char **content, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	*content = ft_strnew(i + 1);
	if (!*content)
		return (-1);
	ft_strncat(*content, str, i);
	return (i);
}

static char	*ft_free(char *content, int r, char *b)
{
	char	*tmp;

	tmp = content;
	content = ft_strdup(content + r);
	if (!content)
		return (NULL);
	free(tmp);
	free(b);
	return (content);
}

static int	read_buf(int fd, char *buf, t_lst *list)
{
	int	r;

	r = read(fd, buf, BUFFER_SIZE);
	while (r > 0)
	{
		buf[r] = '\0';
		list->content = ft_strnjoin(list->content, buf, r);
		if (!list->content)
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
		r = read(fd, buf, BUFFER_SIZE);
	}
	return (r);
}

int	get_next_line(int fd, char **line)
{
	static t_lst	*f;
	t_lst			*l;
	int				r;
	int				i;
	char			*b;

	b = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	l = ft_f(&f, fd);
	if (fd < 0 || !b || read(fd, b, 0) == -1 || !l)
		return (-1);
	r = read_buf(fd, b, l);
	i = ft_strcncat(line, l->content);
	if (i == -1)
		return (-1);
	r = 1;
	if (ft_strlen(b) < BUFFER_SIZE && !(ft_strchr(l->content, '\n')))
		r = 0;
	l->content = ft_free(l->content, i + 1, b);
	if (!l->content)
		return (-1);
	return (r);
}
