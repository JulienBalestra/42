/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:35:52 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 10:37:26 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_new;

	if ((!s) || ((int)len < 0))
		return (NULL);
	str_new = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_new)
		return (NULL);
	ft_bzero(str_new, len + 1);
	ft_strncpy(str_new, s + start, len);
	return (str_new);
}
