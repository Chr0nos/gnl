/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:11:09 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/11 19:30:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	if (read_lenght >= 0)
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
	t_gnls			x;
	int				ret;
	static t_list	*lst_origin;
	t_list			*lst;

	lst = lst_origin;
	while ((lst) && (((t_gnls *)(lst->content))->fd != fd))
		lst = lst->next;
	if (!lst)
	{
		if (!(lst = ft_lstnew((void *)&x, sizeof(x))))
			return (-1);
		((t_gnls*)(lst->content))->fd = fd;
		ft_lstadd(&lst_origin, lst);
		lst = lst_origin;
	}
	*line = 0;
	ret = ft_gnl_read(fd, (t_gnls *)(lst->content));
	if (ret >= 0)
		*line = ((t_gnls *)(lst->content))->buffer;
	if (ret == 0)
		ft_lstremove(&lst, &lst_origin, &free);
	return (ret);
}
