/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/05 18:45:22 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32

static int		ft_gnl_read(const int fd, t_gnls *x)
{
	char	buffer[BUFF_SIZE];
	int		ret;
	int		bpos;

	while (((ret = read(fd, buffer, BUFF_SIZE - 1))) && (x->size += ret))
	{
		buffer[ret] = '\0';
		bpos = ft_strchrpos((char*)buffer, '\n');
		if (bpos)
		{
			buffer[bpos] = '\0';
			x->size -= (ret - bpos);
		}
		if (x->next_buffer)
			ft_strappend(&(x->buffer), x->next_buffer);
		ft_strappend(&(x->buffer), buffer);
		if (bpos)
		{
			x->next_buffer = ft_strdup(buffer + bpos + 1);
			return (1);
		}
	}
	return (0);
}

int				ft_get_next_line(int const fd, char **line)
{
	static t_gnls	*x;

	if (!(x = (t_gnls*)malloc(sizeof(t_gnls))))
		return (-1);
	ft_bzero(&x, sizeof(t_gnls));
	if (!ft_gnl_read(fd, x))
		return (0);
	*line = x->buffer;
	return (1);
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
					printf("%s\n",buffer);
		free(buffer);
		close(fd);
	}
	return (0);
}
