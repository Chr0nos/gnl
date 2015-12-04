/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/04 13:06:19 by snicolet         ###   ########.fr       */
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

static char		*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	p;

	p = 0;
	while ((src[p]) && (p < n))
	{
		dest[p] = src[p];
		p++;
	}
	while (p < n)
		dest[p++] = '\0';
	return (dest);
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
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		total += ret;
		bpos = ft_bpos(buffer);
		ft_strncpy(line[p++], buffer, ((bpos) ? bpos : ret));
		if (bpos)
		{
			free(buffer);
			return (1);
		}
	}
	free(buffer);
	return ((ret < 0) ? -1 : 0);
}

#include <stdlib.h>
#include <stdio.h>

int				main(int ac, char **av)
{
	int		fd;
	char	*buffer = malloc(81);

	if (ac > 1)
	{
		if (!(fd = open(av[1], O_RDONLY)))
			printf("Failed to open file: GTFO NOOB\n");
		else
			printf("%s\n",buffer);
		free(buffer);
		close(fd);
	}
	return (0);
}
