/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:46:36 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:47:44 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (dest && src)
	{
		i = 0;
		str1 = (unsigned char *)dest;
		str2 = (unsigned char *)src;
		while (i < n)
		{
			str1[i] = str2[i];
			if (str2[i] == (unsigned char)c)
				return ((void *)(str1 + i + 1));
			i++;
		}
	}
	return (NULL);
}
