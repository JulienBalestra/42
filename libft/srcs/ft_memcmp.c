/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:48:42 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:50:39 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cuc_1;
	const unsigned char	*cuc_2;
	size_t				i;

	cuc_1 = (const unsigned char *)s1;
	cuc_2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cuc_1[i] != cuc_2[i])
			return ((int)(cuc_1[i] - cuc_2[i]));
		i++;
	}
	return (0);
}
