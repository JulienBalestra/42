/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:00:19 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:01:11 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_item	*return_result(t_sort *merge)
{
	t_item *result;

	result = merge->result;
	free(merge);
	return (result);
}

static void		find_halfway(t_sort *merge)
{
	while (merge->temp && merge->temp->next)
	{
		merge->last = merge->right;
		merge->right = merge->right->next;
		merge->temp = merge->temp->next->next;
	}
}

static void		end_merge(t_sort *merge)
{
	if (!merge->result)
		merge->result = merge->next;
	else
		merge->tail->next = merge->next;
	merge->next->prev = merge->tail;
	merge->tail = merge->next;
}

static void		do_merge(t_sort *merge, t_item *list, t_args *args)
{
	while (list || merge->right)
	{
		if (!merge->right)
		{
			merge->next = list;
			list = list->next;
		}
		else if (!list)
		{
			merge->next = merge->right;
			merge->right = merge->right->next;
		}
		else if (args->compare(list, merge->right, args->options->r) == 1)
		{
			merge->next = list;
			list = list->next;
		}
		else
		{
			merge->next = merge->right;
			merge->right = merge->right->next;
		}
		end_merge(merge);
	}
}

t_item			*merge_sort_list_recursive(t_item *list, t_args *args)
{
	t_sort *merge;

	merge = NULL;
	if ((merge = (t_sort *)malloc(sizeof(t_sort))))
	{
		if (!(list) || !(list->next))
		{
			free(merge);
			return (list);
		}
		set_merge(merge, list);
		find_halfway(merge);
		merge->last->next = NULL;
		list = merge_sort_list_recursive(list, args);
		merge->right = merge_sort_list_recursive(merge->right, args);
		do_merge(merge, list, args);
		return (return_result(merge));
	}
	return (list);
}
