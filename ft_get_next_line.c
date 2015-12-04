/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/04 19:09:31 by snicolet         ###   ########.fr       */
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

static void		ft_strappend(char **s1, const char *s2)
{
	size_t			size;
	char			*d;
	size_t			p;

	p = 0;
	size = ((*s1) ? ft_strlen(*s1) : 0) + ft_strlen(s2);
	if ((d = (char*)malloc(sizeof(char) * (size + 1))))
	{
		while (p < size)
			d[p++] = (((*s1) && (**s1)) ? *(*s1++) : *(s2++));
		d[p] = '\0';
		if (*s1)
			free(*s1);
		*s1 = d;
	}
	else
		*s1 = 0;
}

int				ft_get_next_line(int const fd, char **line)
{
	int		ret;
	size_t	p;
	char	buffer[BUFF_SIZE];
	size_t	bpos;
	size_t	total;

	*line = 0;
	p = 0;
	total = 0;
	while (((ret = read(fd, buffer, BUFF_SIZE -1)) >= 0) && (total += ret))
	{
		buffer[ret] = '\0';
		bpos = ft_bpos((char*)buffer);
		ft_strappend(line, (char*)buffer);
		if (!*line)
			return (-1);
		if (!bpos)
			return (1);
	}
	return ((ret < 0) ? -1 : 0);
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
	char	*buffer = malloc(81);

	test_strappend();
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
