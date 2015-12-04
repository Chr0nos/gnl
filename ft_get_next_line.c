/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/04 16:08:29 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static size_t	ft_bpos(const char *s)
{
	size_t	bpos;

	bpos = 0;
	while (s[bpos])
		if (s[bpos++] == '\n')
			return (bpos - 1);
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t				p;
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	p = 0;
	while (p < size)
	{
		d[p] = s[p];
		p++;
	}
	return (dest);
}

static char		*ft_strappend(char *s1, const char *s2)
{
	const size_t	size = ft_strlen(s1) + ft_strlen(s2);
	char			*d;
	size_t			p;

	if (!(d = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	p = 0;
	while ((p < size) && (*s2))
		d[p++] = ((*s1) ? *(s1++) : *(s2++));
	d[p] = '\0';
	free(s1);
	return (d);
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

	*line = 0;
	if (!(buffer = (char*)malloc(BUFF_SIZE)))
		return (-1);
	p = 0;
	total = 0;
	while (((ret = read(fd, buffer, BUFF_SIZE)) >= 0) && (total += ret))
	{
		bpos = ft_bpos(buffer);
		if (!ft_strappend(*line, buffer))
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
		if ((fd = open(av[1], O_RDONLY)) <= 0)
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
