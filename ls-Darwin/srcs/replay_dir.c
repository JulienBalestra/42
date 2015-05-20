/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replay_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:41:28 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:43:01 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	replay_directory(t_item *items, t_args *args)
{
	t_item	*start;
	int		i;

	start = NULL;
	start = get_start(items);
	i = 0;
	while (items)
	{
		if (items->child)
		{
			if (i == 1)
				ft_putchar('\n');
			ft_get_items(args, items->name, 1);
			i = 1;
		}
		items = items->next;
	}
	del_list(&start, 0);
}

void	display_endline(t_item *items)
{
	t_item	*tmp;
	int		i;

	tmp = NULL;
	tmp = items;
	i = 0;
	while (tmp)
	{
		if (tmp->child == NULL)
			i = 1;
		tmp = tmp->next;
	}
	if (i == 1)
		ft_putchar('\n');
}

void	recurse_browse_arguments_for_items(t_args *args, int opt, int ac,
		char **av)
{
	t_item	*tmp;

	tmp = NULL;
	args->options->re = 0;
	if (browse_arguments_for_items(args, opt, ac, av) == 0)
	{
		args->options->re = 1;
		ft_get_items(args, NULL, 0);
	}
	else
	{
		tmp = merge_sort_list_recursive(args->items, args);
		args->items = NULL;
		if (args->options->l == 1)
			display_file_only(tmp, args);
		else
			file_display(tmp, args);
		display_endline(tmp);
		args->options->re = 1;
		replay_directory(tmp, args);
	}
}
