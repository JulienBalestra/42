/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:34:47 by jubalest          #+#    #+#             */
/*   Updated: 2015/02/20 09:35:35 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst && del)
	{
		while ((*alst) != NULL)
		{
			del((*alst)->content, ((*alst)->content_size));
			*alst = (*alst)->next;
		}
	}
	free(*alst);
	*alst = NULL;
}
