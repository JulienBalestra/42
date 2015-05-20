/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:42:35 by jubalest          #+#    #+#             */
/*   Updated: 2015/03/11 12:48:19 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst;
	t_list *tmp_link;
	t_list *start_link;

	start_link = NULL;
	if (!lst || !f)
		return (NULL);
	tmp_link = f(lst);
	new_lst = ft_lstnew(tmp_link->content, tmp_link->content_size);
	if (new_lst)
	{
		start_link = new_lst;
		while (lst->next != NULL)
		{
			tmp_link = f(lst->next);
			new_lst->next = ft_lstnew(tmp_link->content,
					tmp_link->content_size);
			if (new_lst->next)
			{
				lst = lst->next;
				new_lst = new_lst->next;
			}
		}
	}
	return (start_link);
}
