/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:33:52 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:34:29 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*cursor;

	if (*alst && new)
	{
		cursor = *alst;
		while (cursor->next != NULL)
			cursor = cursor->next;
		cursor->next = new;
	}
}
