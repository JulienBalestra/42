/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:01:20 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:01:21 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void set_merge(t_sort *merge, t_item *list)
{
	if (merge)
	{
		merge->right = list;
		merge->temp = list;
		merge->last = list;
		merge->result = NULL;
		merge->next = NULL;
		merge->tail = NULL;
	}
}
