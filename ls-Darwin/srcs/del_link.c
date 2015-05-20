/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:10:21 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:12:03 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			destroy_link(t_item *link)
{
	if (link)
	{
		if (link->child)
			del_list(&(link->child), 0);
		if (link->name)
			free(link->name);
		if (link->stats)
			free(link->stats);
		if (link->parent)
			free(link->path);
		link->name = NULL;
		link->parent = NULL;
		link->next = NULL;
		link->prev = NULL;
		link->child = NULL;
		link->path = NULL;
		link->stats = NULL;
		free(link);
		link = NULL;
	}
}

static void		del_link_forward(t_item **alist)
{
	t_item	*current;

	while (*alist)
	{
		current = (*alist)->next;
		destroy_link(*alist);
		*alist = current;
	}
	current = NULL;
}

static void		del_link_backward(t_item **alist)
{
	t_item	*current;

	while (*alist)
	{
		current = (*alist)->prev;
		destroy_link(*alist);
		*alist = current;
	}
	current = NULL;
}

static void		del_both_ways(t_item **alist)
{
	t_item *forward;

	forward = (*alist)->next;
	del_link_forward(&forward);
	del_link_backward(alist);
}

void			del_list(t_item **alist, int way)
{
	if (*alist)
	{
		if (way == 0)
			del_both_ways(alist);
		else if (way == 1)
			del_link_forward(alist);
		else if (way == -1)
			del_link_backward(alist);
		free(*alist);
		*alist = NULL;
	}
}
