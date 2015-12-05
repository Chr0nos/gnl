/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/05 16:24:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32

static int		ft_load_file(const int fd, t_gnls *x)
{
	char	buffer[BUFF_SIZE];
	int		ret;
	int		bpos;

	while (((ret = read(fd, buffer, BUFF_SIZE -1))) && (x->size += ret))
	{
		buffer[ret] = '\0';
		bpos = ft_strchrpos((char*)buffer);
		if (bpos)
		{
			buffer[bpos] = '\0';
			x->size -= (ret - bpos);
		}
		ft_strappend(&(x->buffer), buffer);
		if (bpos)
		{
			ft_lstpush_back(&(x->lst), ft_lstnewstr(x->buffer));
			(x->lines)++;
			x->buffer[0] = '\0';
		}
	}
}

int				ft_get_next_line(int const fd, char **line)
{
	static t_gnls	x;

	if (!(x = (t_gnls*)malloc(sizeof(t_gnls))))
		return (-1);
	ft_memset(x, 0, sizeof(t_gnls));
	*line = 0;
	return (0);
}

//DELETE EVRYTHING BELLOW THIS LINE (INCLUDED)
#include <stdlib.h>
#include <stdio.h>

void			test_strappend()
{
	char	*x;

	x = 0;
	ft_strappend(&x, "abc");
	ft_strappend(&x, "def");
	printf("%s\n", x);
	free(x);
}

int				main(int ac, char **av)
{
	int		ret;
	int		fd;
	char	*buffer;

	buffer = 0;
	test_strappend();
	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) <= 0)
			printf("Failed to open file: GTFO NOOB\n");
		else
			while ((ret = ft_get_next_line(fd, &buffer)))
				printf("%s\n",buffer);
		free(buffer);
		close(fd);
	}
	return (0);
}
