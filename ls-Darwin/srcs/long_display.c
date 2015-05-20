/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:53:43 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:01:15 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	display_child(t_item *items, t_args *args)
{
	t_item	*child;
	int		i;

	i = 0;
	child = items->child;
	iter_on_links(child, args->ld, 0);
	display_total_blocks(args->ld->total_blocks);
	while (child)
	{
		selected_print(child, args);
		child = child->next;
		i = 1;
	}
	return (i);
}

int			display_file_only(t_item *items, t_args *args)
{
	t_item	*start;
	int		ret;

	start = items;
	iter_on_links(items, args->ld, 1);
	ret = 0;
	while (items)
	{
		if (items->child == NULL)
		{
			ret = 1;
			selected_print(items, args);
		}
		items = items->next;
	}
	items = start;
	return (ret);
}

static void	browse_directory_to_display(t_item *items, t_args *args, int ret)
{
	int i;

	i = 0;
	while (items)
	{
		if (items->child)
		{
			if (ret == 1 || i == 1)
				ft_putchar('\n');
			if (items->next || items->prev)
			{
				if (args->options->q == 1)
					ft_putchar('"');
				ft_putstr(items->name);
				if (args->options->q == 1)
					ft_putchar('"');
				ft_putstr(":\n");
			}
			i = display_child(items, args);
		}
		items = items->next;
	}
}

void		long_display(t_item *items, t_args *args)
{
	int ret;

	ret = 0;
	items = merge_sort_list_recursive(items, args);
	ret = display_file_only(items, args);
	browse_directory_to_display(items, args, ret);
}
