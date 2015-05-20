/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_indent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:20:39 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:21:45 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	display_blank_for_digits(int use_case, int indent)
{
	int len;

	len = ft_nbrlen(use_case);
	while (len < indent)
	{
		ft_putchar(' ');
		len++;
	}
}

void	display_blank_for_str(int strlen, int indent, int q)
{
	if (q == 1)
		indent = indent - 2;
	while (strlen - 1 < indent - 2)
	{
		ft_putchar(' ');
		strlen++;
	}
	ft_putchar(' ');
}
