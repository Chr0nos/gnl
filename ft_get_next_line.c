/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/06 01:17:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32

static int		ft_add_pending(char *buffer, t_gnls *x)
{
	size_t		ppos;

	ft_strappend(&(x->pending_buffer), buffer);
	ppos = ft_strchrpos(x->pending_buffer, '\n');
	return (ppos);
}

static int		ft_read_data(char *buffer, t_gnls *x)
{
	const size_t	bpos = ft_strchrpos(buffer, '\n');
	size_t			ppos;
	char			*tmp;

	ppos = ft_add_pending(buffer, x);
	if (ppos)
	{
		x->buffer = strndup(x->pending_buffer, ppos);
		x->buffer[ppos] = '\0';
		if (!(tmp = ft_strdup(x->pending_buffer + ppos)))
			return (-1);
		free(x->pending_buffer);
		x->pending_buffer = tmp;
		return (1);
	}
	else
		ft_strappend(&(x->pending_buffer), buffer);
	return (0);
}

static int		read_please(int fd, char *buffer)
{
	int		ret;

	ret = read(fd, buffer, BUFF_SIZE);
	buffer[ret] = '\0';
	return (ret);
}

static int		ft_gnl_read(const int fd, t_gnls *x)
{
	char	buffer[BUFF_SIZE + 1];
	int		ret;

	while (1)
	{
		ret = read_please(fd, buffer);
		if (ret == 0)
		{
			x->buffer = x->pending_buffer;
			return (1);
		}
		if (ft_read_data(buffer, x))
			return (1);
	}
	if (ret < 0)
		return (-1);
	return (0);
}

int				ft_get_next_line(int const fd, char **line)
{
	static t_gnls	*x = 0;

	*line = 0;
	if (!x)
	{
		if (!(x = (t_gnls*)malloc(sizeof(t_gnls))))
			return (-1);
		x->buffer = 0;
		x->pending_buffer = 0;
		x->line_ok = 0;
	}
	if (ft_gnl_read(fd, x))
		*line = x->buffer;
	return (((*line) ? 1 : 0));
}

//DELETE EVRYTHING BELLOW THIS LINE (INCLUDED)
#include <stdlib.h>
#include <stdio.h>

int				main(int ac, char **av)
{
	int		ret;
	int		fd;
	char	*buffer;

	buffer = 0;
	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) <= 0)
			printf("Failed to open file: GTFO NOOB\n");
		else
			while ((ret = ft_get_next_line(fd, &buffer)))
				if (buffer)
				{
					printf("%s\n",buffer);
					ft_strdel(&buffer);
				}
		close(fd);
	}
	return (0);
}
