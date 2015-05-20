/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:47:53 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:48:16 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*uc;
	size_t			i;

	uc = (unsigned char *)s;
	if (uc)
	{
		i = 0;
		while (i < n)
		{
			if (*uc == (unsigned char)c)
				return ((void *)uc);
			i++;
			uc++;
		}
	}
	return (NULL);
}
