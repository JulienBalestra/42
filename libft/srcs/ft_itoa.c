/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:30:41 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:32:54 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char			*str_new(int neg, size_t size)
{
	char	*str;
	
	str = NULL;
	if ((str = (char *)malloc(sizeof(char) * size + 1)))
	{
		if (neg)
			str[0] = '-';
		str[size] = '\0';
	}
	return (str);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				neg;
	int				len;
	int				i;
	unsigned int	j;

	str = NULL;
	neg = 0;
	if (n < 0)
		neg = 1;
	len = ft_nbrlen(n) + neg;
	j = ft_absint(n);
	if ((str = str_new(neg, len)))
	{		
		i = len - 1;
		while (i >= neg)
		{
			str[i] = (j % 10) + 48;
			j = j / 10;
			i--;
		}		
	}
	return (str);
}
