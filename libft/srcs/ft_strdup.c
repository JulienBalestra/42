/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:13:02 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 10:13:53 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *str)
{
	char	*new;
	size_t	i;
	size_t	len_str;

	if (str == NULL)
		return (NULL);
	len_str = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (len_str + 1));
	if (new != NULL)
	{
		i = 0;
		while ((str[i] != '\0') && (i < len_str))
		{
			new[i] = str[i];
			i++;
		}
		new[i] = '\0';
	}
	return (new);
}
