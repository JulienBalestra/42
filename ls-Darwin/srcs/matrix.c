/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:04:08 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:28:54 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_item		***create_matrix(t_sd *sd)
{
	t_item	***matrix;
	t_item	**lin;
	int		l;
	int		c;

	matrix = NULL;
	lin = NULL;
	l = 0;
	c = 0;
	if ((matrix = (t_item ***)malloc(sizeof(t_item ***) * (sd->nb_lines + 1))))
	{
		while (l < sd->nb_lines)
		{
			if ((lin = (t_item **)malloc(sizeof(t_item **) * (sd->nb_col + 1))))
			{
				c = 0;
				while (c < sd->nb_col)
					lin[c++] = NULL;
				matrix[l] = lin;
			}
			l++;
		}
		matrix[l] = NULL;
	}
	return (matrix);
}

static void feed_matrix(t_item ***matrix, t_item *items, t_sd *sd, int dir)
{
	int		l;
	int		c;

	l = 0;
	c = 0;
	if ((items = get_start(items)))
	{
		while (items)
		{
			if (l == sd->nb_lines)
			{
				l = 0;
				c++;
			}
			if (dir == 0 && items->child == NULL)
				matrix[l++][c] = items;
			else
				matrix[l++][c] = items;
			items = items->next;
		}
		while (l < sd->nb_lines)
			matrix[l++][c] = NULL;
		items = get_start(items);
	}
}

static void display_matrix(t_item ***matrix, t_args *args)
{
	int l;
	int c;

	l = 0;
	c = 0;
	while (l < args->sd->nb_lines - 1)
	{
		if (c == args->sd->nb_col)
		{
			c = 0;
			l++;
			ft_putchar('\n');
		}
		if (matrix[l][c])
		{
			display_name(matrix[l][c], args, 0);
			if (args->sd->nb_col > 1)
				display_blank_for_str(ft_strlen(matrix[l][c]->name),
					args->sd->len_items, args->options->q);
			c++;
		}
		else
			break ;
	}
	ft_putchar('\n');
}

static void no_need_matrix(t_item *items, t_args *args, int directory)
{
	int	i;

	i = 0;
	if ((items = get_start(items)))
	{
		while (items)
		{
			if (items->child == NULL)
			{
				i = 1;
				display_name(items, args, directory);
				ft_putstr("  ");
			}
			items = items->next;
		}
		if (i == 1)
			ft_putchar('\n');
		items = get_start(items);
	}
}

int			run_matrix(t_args *args, t_item *items, int directory)
{
	t_item	***matrix;

	matrix = NULL;
	if (args->sd->nb_items == 0)
		return (0);
	set_matrix_size(args->sd, args->sd_ts);
	if (args->sd->nb_lines < 3)
		no_need_matrix(items, args, directory);
	else if (args->sd->nb_col == 1)
		return (1);
	else
	{
		matrix = create_matrix(args->sd);
		feed_matrix(matrix, items, args->sd, directory);
		display_matrix(matrix, args);
		free_matrix(matrix);
	}
	return (0);
}
