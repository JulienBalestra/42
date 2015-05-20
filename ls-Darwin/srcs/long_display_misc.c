/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:01:31 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:01:32 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	selected_print(t_item *items, t_args *args)
{
	display_protection(items->stats->st_mode, items->path);
	display_hard_link(items->stats->st_nlink, args->ld->i_nlink);
	display_id(items->stats, args);
	display_dev_or_size(items->stats, args->ld);
	display_date(items->stats->st_mtime, args->ld);
	display_name(items, args, 0);
	display_symbolic_link(items, args);
	ft_putchar('\n');
}

void	iter_on_links(t_item *items, t_ld *ld, int file_only)
{
	t_item	*start;

	set_ld(ld);
	items = get_start(items);
	start = items;
	while (items)
	{
		if (file_only && items->child == NULL)
			get_ld(items->stats, ld);
		else if (file_only == 0)
			get_ld(items->stats, ld);
		items = items->next;
	}
	items = start;
}

void	display_total_blocks(int total_blocks)
{
	ft_putstr("total ");
	ft_putnbr(total_blocks);
	ft_putchar('\n');
}
