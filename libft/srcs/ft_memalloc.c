/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:45:12 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:46:27 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	size_t	i;
	char	*mem;

	mem = (char *)malloc(sizeof(*mem) * size);
	if (mem != NULL)
	{
		i = 0;
		while (i < size)
		{
			mem[i] = '\0';
			i++;
		}
	}
	return ((void *)mem);
}
