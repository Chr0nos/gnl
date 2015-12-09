/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/09 12:49:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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
	if (rest_len <= 0)
	{
		free(*pending);
		*pending = NULL;
	}
	else if (!(tmp = ft_strdup(*pending + offset)))
		return ;
	if (*pending)
		free(*pending);
	*pending = tmp;
}

static int		ft_read_data(char *buffer, t_gnls *x)
{
	int			read_lenght;
	int			rest_lenght;

	add_pending(buffer, x);
	if (x->pb == NULL)
		return (-1);
	read_lenght = ft_strchrpos(x->pb, '\n');
	rest_lenght = 0;
	if ((read_lenght > 0) || ((read_lenght == 0) && (x->pb[0] == '\n')))
	{
		rest_lenght = ft_strlen(x->pb) - read_lenght;
		x->buffer = ft_strndup(x->pb, read_lenght);
		x->buffer[read_lenght] = '\0';
		rotate_pending(&x->pb, read_lenght + 1, rest_lenght);
		return (1);
	}
	return (0);
}

static int		ft_gnl_read(const int fd, t_gnls *x)
{
	char	buffer[BUFF_SIZE + 1];
	int		ret;
	int		ret_b;

	x->buffer = 0;
	ret = 1;

	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		if (ret < 0)
			return (ret);
		buffer[ret] = '\0';
		ret_b = ft_read_data(buffer, x);
		if (ret_b == 1)
			return (1);
	}
	buffer[0] = '\0';
	while ((ret_b = ft_read_data(buffer, x)))
	{
		if (ret_b < 0)
			return (ret_b);
		if (ret_b == 1)
			return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
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
		{
			while ((ret = get_next_line(fd, &buffer)))
			{
				printf("[%d] %s\n", p++, buffer);
				ft_strdel(&buffer);
				if (ret == -1)
				{
					ft_putendl("erreur");
					break ;
				}
				if (ret == 0)
					return (0);
			}
			close(fd);
		}
	}
	return (0);
}
