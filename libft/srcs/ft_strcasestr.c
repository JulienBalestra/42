/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:05:53 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 10:06:48 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strcasestr(const char *haystack, const char *needle)
{
	size_t i;
	size_t n;
	size_t j;

	i = 0;
	n = 0;
	j = 0;
	while ((haystack[i] != '\0') && (needle[n] != '\0'))
	{
		if (ft_tolower(haystack[i]) == ft_tolower(needle[n]))
			n++;
		i++;
	}
	if (n == ft_strlen(needle))
	{
		while (j < (i - n))
		{
			haystack++;
			j++;
		}
		return ((char *)haystack);
	}
	else
		return (NULL);
}
