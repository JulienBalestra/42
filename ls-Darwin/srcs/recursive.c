/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:34:33 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:35:38 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	short_display_root_items(t_item *root, t_args *args)
{
	t_item		*start;
	int			ret;

	ret = 1;
	start = root;
	if (args->options->c == 1)
	{
		iter_for_len(root, args, 0);
		ret = run_matrix(args, root, 0);
	}
	if (ret == 1)
	{
		while (root)
		{
			display_name(root, args, 0);
			ft_putchar('\n');
			root = root->next;
		}
	}
	root = start;
}

static void	long_display_root_items(t_item *items, t_args *args)
{
	t_item		*start;

	start = items;
	iter_on_links(items, args->ld, 1);
	display_total_blocks(args->ld->total_blocks);
	while (items)
	{
		selected_print(items, args);
		items = items->next;
	}
	items = start;
}

static void	browse_root(t_item *child_to_parent, t_args *args)
{
	t_item *root;

	root = NULL;
	if (child_to_parent)
	{
		root = child_to_parent;
		if (child_to_parent->parent->parent == NULL)
		{
			if (args->inputs > 2)
			{
				display_name(root->parent, args, 1);
				ft_putstr(":\n");
			}
		}
		if (args->options->l == 0)
			short_display_root_items(root, args);
		else
			long_display_root_items(root, args);
	}
}

void		deep_in_directories(t_item *child_to_parent, t_args *args)
{
	if (args->options->re == 1)
	{
		browse_root(child_to_parent, args);
		while (child_to_parent)
		{
			recurse_in_directory(child_to_parent, args);
			child_to_parent = child_to_parent->next;
		}
	}
}
