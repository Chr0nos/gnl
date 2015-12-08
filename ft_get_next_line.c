/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/08 18:08:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32


#include <stdio.h>

static void		add_pending(char *buffer, t_gnls *x)
{
	char	*tmp;

	if (x->pb)
	{
		tmp = x->pb;
		x->pb = ft_strjoin(x->pb, buffer);
		free(tmp);
	}
	else
		x->pb = ft_strdup(buffer);
}

static void		rotate_pending(char **pending, size_t offset, int rest_len)
{
	char	*tmp;

	tmp = NULL;
	if ((rest_len > 0) && (!(tmp = ft_strdup(*pending + offset))))
		return ;
	if (*pending)
		free(*pending);
	*pending = tmp;
}

static int		ft_read_data(char *buffer, t_gnls *x, const int ret)
{
	int			pending_lenght;
	int			read_lenght;
	int			rest_lenght;
	char		*read_start;

	add_pending(buffer, x);
	if (x->pb == NULL)
		return (-1);
	pending_lenght = ft_strlen(x->pb);
	read_start = ft_strchr(x->pb, '\n');
	if (read_start)
		read_lenght = read_start - x->pb;
	else if ((ret <= 0) && (x->pb))
	{
		//ici lire le prochain \n dans le peding
		read_lenght = pending_lenght;
	}
	else
		read_lenght = 0;
	rest_lenght = pending_lenght - read_lenght;
	printf("rest lenght: %d --- read: %d --- pending len: %d\n", rest_lenght, read_lenght, pending_lenght);
	if (read_lenght > 0)
	{
		x->buffer = ft_strndup(x->pb, read_lenght);
		x->buffer[read_lenght] = '\0';
		rotate_pending(&x->pb, read_lenght + 1, rest_lenght);
		return (1);
	}
	else if (ret <= 0)
		return (1);
	return (0);
}

static int		ft_gnl_read(const int fd, t_gnls *x)
{
	char	buffer[BUFF_SIZE + 1];
	int		ret;
	int		ret_b;

	x->buffer = 0;
	ret = 1;
	while (1)
	{
		if (ret > 0)
		{
			ret = read(fd, buffer, BUFF_SIZE);
			if (ret < 0)
				return (ret);
			buffer[ret] = '\0';
		}
		ret_b = ft_read_data(buffer, x, ret);
		if ((ret_b == 0) || (ret_b == 1))
			return (ret);
		else if (ret < 0)
		{
			ft_putendl("gnl read internal error 1");
			x->buffer = 0;
			x->pb = 0;
			return (ret);
		}
	}
}

//TODO: RENOMER LA FONCTiON SANS LE FT_
int				ft_get_next_line(int const fd, char **line)
{
	static t_gnls	x;
	int				ret;

	*line = 0;
	ret = ft_gnl_read(fd, &x);
	if (ret >= 0)
		*line = x.buffer;
	return (ret);
}

//DELETE EVRYTHING BELLOW THIS LINE (INCLUDED)

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
		{
			while (1)
			{
				ret = ft_get_next_line(fd, &buffer);
				if (ret >= 0)
				{
					printf("[%d] %s\n", p++, buffer);
					ft_strdel(&buffer);
					if (ret == 0)
						return (0);
				}
				else
					return (0);
			}
			close(fd);
		}
	}
	return (0);
}
