/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 18:40:30 by jubalest          #+#    #+#             */
/*   Updated: 2015/03/09 18:40:45 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strndup(const char *s, size_t n)
{
	char	*new_str;
	size_t	i;

	if (!s && ft_strlen(s) > n)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (n));
	if (new_str != NULL)
	{
		i = 0;
		while ((s[i] != '\0') && (i < n))
		{
			new_str[i] = s[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}
