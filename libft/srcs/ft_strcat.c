/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:06:55 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 10:07:32 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *dest, const char *src)
{
	char	*new_str;

	new_str = dest;
	while (*dest)
		dest++;
	while ((*dest = *src))
	{
		dest++;
		src++;
	}
	return (new_str);
}
