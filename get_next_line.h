/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 14:15:48 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 16:00:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# define BUFF_SIZE 999

typedef struct	s_gnlstatic_of_doom
{
	int			fd;
	int			memory_padding;
	char		*buffer;
	char		*pb;
}				t_gnls;

int				get_next_line(int const fd, char **line);

#endif
