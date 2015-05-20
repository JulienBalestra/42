/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:50:48 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:56:01 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memcpy(void *dest, const void *src, size_t n)
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
			i++;
		}
	}
	return ((void *)dest);
}
