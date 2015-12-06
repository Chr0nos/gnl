/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/06 19:56:28 by snicolet         ###   ########.fr       */
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

static int		ft_read_data(char *buffer, t_gnls *x, int ret)
{
	int				ppos;
	char			*tmp;

	ppos = ft_add_pending(buffer, x);
	if (!ret)
		ppos = ft_strlen(x->pending_buffer);
	//si un \n a ete trouve dans le pending buffer apres ajout du buffer de lecture
	if (ppos >= 0)
	{
		//on lis la premiere partie avant le \n et on delimite la fin du buffer
		x->buffer = strndup(x->pending_buffer, ppos + 1);
		x->buffer[ppos] = '\0';
		//on alloue l espace pour le nouveau buffer de pending et on copie
		tmp = 0;
		if (x->pending_buffer[ppos] != '\0')
			if (!(tmp = ft_strdup(x->pending_buffer + ppos + 1)))
				return (-1);
		//on libere l ancien pending
		free(x->pending_buffer);
		//et on repointe le pending vers la nouvelle zone memoire
		x->pending_buffer = tmp;
		//et on retourne 1 pour dire qu une ligne est ok
		return (1);
	}
	//sinon on ne fais que dalle et on return 0 (demande de nouvelle lecture)
	else
	{
		x->buffer = 0;
		return (1);
	}
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

	x->buffer = 0;
	while (1)
	{
		ret = read_please(fd, buffer);
		ret = ft_read_data(buffer, x, ret);
		if (ret == 1)
			return (ret);
		else if (ret < 0)
		{
			ft_putendl("gnl read internal error 1");
			x->buffer = 0;
			x->pending_buffer = 0;
			return (ret);
		}
	}
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
	int		p;

	buffer = 0;
	p = 0;
	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) <= 0)
			printf("Failed to open file: GTFO NOOB\n");
		else
			while ((ret = ft_get_next_line(fd, &buffer)))
				if (buffer)
				{
					printf("[%d] %s\n", p++, buffer);
					ft_strdel(&buffer);
				}
		close(fd);
	}
	return (0);
}
