/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:03:36 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:03:51 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_item	*get_start(t_item *link)
{
	if (link)
	{
		while (link->prev)
			link = link->prev;
	}
	return (link);
}

t_item	*get_end(t_item *link)
{
	if (link)
	{
		while (link->next)
			link = link->next;
	}
	return (link);
}

void	remove_link(t_item *link)
{
	t_item	*current;

	if (link)
	{
		if (link->next)
		{
			current = link->next;
			current->prev = link->prev;
		}
		if (link->prev)
		{
			current = link->prev;
			current->next = link->next;
		}
		destroy_link(link);
		link = current;
	}
}
