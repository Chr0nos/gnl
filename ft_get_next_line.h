/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 14:15:48 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/05 17:45:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <string.h>

typedef struct	s_gnlstatic_of_doom
{
	char		*buffer;
	char		*next_buffer;
	size_t		pos;
	size_t		size;
}				t_gnls;

int				ft_get_next_line(int const fd, char **line);

#endif
