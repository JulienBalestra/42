/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:29:19 by jubalest          #+#    #+#             */
/*   Updated: 2015/03/09 18:41:49 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nb_string(char const *s, char sep, int len)
{
	int		i;
	int		nb_sep;

	i = 0;
	nb_sep = 0;
	while (i < len)
	{
		if ((s[i] == sep) && (i != 0))
		{
			if (s[i - 1] != sep)
				nb_sep++;
		}
		i++;
	}
	if (i != 0)
		nb_sep++;
	return (nb_sep);
}

static char *ft_strnew_n_to_i_alloc(char const *s, int n, int i)
{
	char	*str;
	int		k;

	str = (char *)malloc(sizeof(char) * (size_t)(i - n));
	k = 0;
	if (str)
	{
		while (n != i)
		{
			str[k] = s[n];
			n++;
			k++;
		}
		str[k] = '\0';
	}
	return (str);
}

static void	ft_do_split(char const *s, char sep, int len, char **split)
{
	int		k;
	int		n;
	int		i;

	k = 0;
	n = -1;
	i = 0;
	while (i < len)
	{
		if (s[i] != sep)
		{
			if (n == -1)
				n = i;
			if (i == len - 1)
				split[k] = ft_strnew_n_to_i_alloc(s, n, i + 1);
		}
		else if ((i != 0) && (s[i - 1] != sep))
		{
			split[k] = ft_strnew_n_to_i_alloc(s, n, i);
			k++;
			n = -1;
		}
		i++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		len;

	len = ft_strlen(s);
	while ((s[len - 1] == c) && (len >= 0))
		len--;
	split = (char **)malloc(sizeof(char *) *
					(size_t)ft_nb_string(s, c, len) + 1);
	if (split == NULL)
		return (NULL);
	ft_do_split(s, c, len, split);
	split[ft_nb_string(s, c, len)] = NULL;
	return (split);
}
