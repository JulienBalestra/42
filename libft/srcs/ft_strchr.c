/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:07:42 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 10:09:30 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char		*ft_strchr(const char *s, int c)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!s)
		return ((void *)NULL);
	while (s[len] != '\0')
		len++;
	while ((i < len) && (s[i] != c))
		i++;
	if (s[i] == c)
		return (char *)&s[i];
	return ((void *)NULL);
}
