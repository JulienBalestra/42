/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:22:08 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 10:22:45 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = s1;
	if (!s1 || !s2)
		return ((void *)0);
	while (*s1 != '\0')
		s1++;
	while ((*s2 != '\0') && (i < n))
	{
		*s1 = *s2;
		i++;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (str);
}
