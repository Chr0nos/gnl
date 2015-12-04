/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/04 14:52:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32

static size_t	ft_bpos(const char *s)
{
	size_t	bpos;

	bpos = 0;
	while (s[bpos])
		if (s[bpos++] == '\n')
			return (bpos - 1);
	return (0);
}

static char		*ft_strndup(const char *s, size_t n)
{
	size_t	p;
	char	*x;

	if (!(x = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	p = 0;
	while ((s[p]) && (p < n))
	{
		x[p] = s[p];
		p++;
	}
	x[p] = '\0';
	return (x);
}
static int		yolo(char *x, int y)
{
	free(x);
	return (y);
}
int				ft_get_next_line(int const fd, char **line)
{
	int		ret;
	size_t	p;
	char	*buffer;
	size_t	bpos;
	size_t	total;

	if (!(buffer = (char*)malloc(BUFF_SIZE)))
		return (-1);
	p = 0;
	total = 0;
	while ((ret = read(fd, buffer, BUFF_SIZE)) >= 0)
	{
		total += ret;
		bpos = ft_bpos(buffer);
		if (!(*line = ft_strndup(buffer, (bpos) ? bpos : ret)))
			return (yolo(buffer, 1));
		if ((bpos) || (!ret))
			return (yolo(buffer, 1));
	}
	return (yolo(buffer, (ret < 0) ? -1 : 0));
}

#include <stdlib.h>
#include <stdio.h>

int				main(int ac, char **av)
{
	int		ret;
	int		fd;
	char	*buffer = malloc(81);

	if (ac > 1)
	{
		if (!(fd = open(av[1], O_RDONLY)))
			printf("Failed to open file: GTFO NOOB\n");
		else
		{
			ret = ft_get_next_line(fd, &buffer);
			printf("%s\n",buffer);
		}
		free(buffer);
		close(fd);
	}
	return (0);
}
