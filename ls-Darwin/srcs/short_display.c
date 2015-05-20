/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:43:18 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:57:35 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	child_display(t_item *items, t_args *args)
{
	t_item	*child;
	int		ret;

	ret = 1;
	child = items->child;
	child = merge_sort_list_recursive(child, args);
	if (args->options->c == 1)
	{
		iter_for_len(child, args, 0);
		ret = run_matrix(args, child, 0);
	}
	if (ret == 1)
	{
		while (child)
		{
			display_name(child, args, 0);
			ft_putchar('\n');
			child = child->next;
		}
	}
}

int			file_display(t_item *items, t_args *args)
{
	int		ret;
	t_item	*start;

	start = get_start(items);
	ret = 1;
	if (args->options->c == 1)
	{
		iter_for_len(items, args, 0);
		ret = run_matrix(args, items, 0);
	}
	if (ret == 1)
	{
		ret = 0;
		iter_file_display(items, args, ret);
	}
	items = start;
	return (ret);
}

static void directory_display(t_item *items, t_args *args, int ret)
{
	while (items)
	{
		if (items->child)
		{
			if (items->prev || ret == 1)
				ft_putchar('\n');
			if (items->next || items->prev)
			{
				display_name(items, args, 1);
				ft_putstr(":\n");
			}
			child_display(items, args);
		}
		else if (is_directory(items) && try_rights(items->path) == 1
			&& args->inputs > 1 && args->options->d == 0)
		{
			if (items->prev || is_other_dir(items) == 1)
				ft_putchar('\n');
			display_name(items, args, 1);
			ft_putstr(":\n");
		}
		else if (is_directory(items) && try_rights(items->path) == 0)
			no_directory_display(items, args);
		items = items->next;
	}
}

void		short_display(t_item *items, t_args *args)
{
	int ret;

	ret = 0;
	items = get_start(items);
	items = merge_sort_list_recursive(items, args);
	ret = file_display(items, args);
	directory_display(items, args, ret);
}
