/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:07:05 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:07:21 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	verbose_invalid_option(char *av)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(get_illegal(av), 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("usage: ls [-1lRartSGgdQUfC and color] [file ...]\n", 2);
}

void	verbose_not_enough_memory(void)
{
	ft_putstr_fd("Not enough memory\n", 2);
	ft_putstr_fd("Please go get some\n", 2);
}
