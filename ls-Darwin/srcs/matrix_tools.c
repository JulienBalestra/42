/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:29:12 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:31:37 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		min(int a, int b)
{
	return (a >= b ? b : a);
}

int		round_up(int a, int b)
{
	int ret;

	ret = 0;
	ret = a / b;
	return (ret);
}

void	set_matrix_size(t_sd *sd, int sd_ts)
{
	sd->len_items = sd->len_items + 2;
	if (sd->len_items > sd_ts)
		sd->nb_col = 1;
	else
		sd->nb_col = min(sd->nb_items, (sd_ts / sd->len_items));
	sd->nb_lines = round_up(sd->nb_items, sd->nb_col) + 1;
}

void	free_matrix(t_item ***matrix)
{
	int i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}
