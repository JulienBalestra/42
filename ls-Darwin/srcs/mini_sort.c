/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:31:52 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:33:47 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	ft_swap_s(char **s1, char **s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void		get_sorted_av(char **av, int opt, int ac)
{
	int	i;
	int	j;

	i = opt;
	while (i < ac)
	{
		j = opt;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) < 0)
			{
				ft_swap_s(&av[i], &av[j]);
			}
			j++;
		}
		i++;
	}
}
