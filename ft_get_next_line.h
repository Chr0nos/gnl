/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 14:15:48 by snicolet          #+#    #+#             */
/*   Updated: 2015/12/05 23:27:19 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <string.h>

typedef struct	s_gnlstatic_of_doom
{
	char		*buffer;
	char		*pending_buffer;
	int			line_ok;
}				t_gnls;

int				ft_get_next_line(int const fd, char **line);

#endif
