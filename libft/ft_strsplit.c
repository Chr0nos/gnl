/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 12:27:16 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/07 16:06:24 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_strsplit(const char *str, char separator)
{
	char	**split;
	size_t	len;
	size_t	space;

	if (!(split = malloc(sizeof(char*) * ft_strsplit_count(str, separator))))
		return (NULL);
	space = 0;
	while (*str)
	{
		while (*str == separator)
			str++;
		if (*str)
		{
			len = ft_strsublen(str, separator);
			split[space++] = ft_strndup(str, len);
			str += len;
		}
	}
	split[space] = 0;
	return (split);
}
