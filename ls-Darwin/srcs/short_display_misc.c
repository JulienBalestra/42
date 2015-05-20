/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_display_misc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:57:49 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:00:03 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		try_rights(char *path)
{
	DIR	*fd_file;

	fd_file = NULL;
	if ((fd_file = open_dir(path)))
	{
		closedir(fd_file);
		return (1);
	}
	else
		return (0);
}

int		is_other_dir(t_item *items)
{
	t_item *start;

	start = NULL;
	start = get_start(items);
	items = start;
	while (items)
	{
		if (is_directory(items) == 0)
		{
			items = start;
			return (1);
		}
		items = items->next;
	}
	items = start;
	return (0);
}

void	iter_file_display(t_item *items, t_args *args, int ret)
{
	while (items)
	{
		if (is_directory(items) == 0)
		{
			ret = 1;
			display_name(items, args, 0);
			ft_putchar('\n');
		}
		else if (args->options->d == 1 && is_directory(items) == 1)
		{
			ret = 1;
			display_name(items, args, 0);
			ft_putchar('\n');
		}
		items = items->next;
	}
}

void	no_directory_display(t_item *items, t_args *args)
{
	if (items->prev)
		ft_putchar('\n');
	if (args->inputs > 1)
	{
		display_name(items, args, 1);
		ft_putstr(":\n");
	}
	cannot_open(items, args);
}
