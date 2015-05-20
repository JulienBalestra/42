/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:58:43 by jubalest          #+#    #+#             */
/*   Updated: 2015/03/11 12:49:51 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*uc;
	size_t			i;

	i = 0;
	uc = NULL;
	if (s)
	{
		uc = (unsigned char *)s;
		while (i < n)
		{
			uc[i] = c;
			i++;
		}
	}
	return (void *)uc;
}
