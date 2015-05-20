/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goodies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:47:56 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:52:04 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	set_color(mode_t mode)
{
	if (S_ISDIR(mode))
		ft_putstr("\033[0;34m\033[1m");
	else if (S_ISLNK(mode))
		ft_putstr("\033[0;36m\033[1m");
	else if (S_ISSOCK(mode))
		ft_putstr("\033[01;35m\033[1m");
	else if (S_ISBLK(mode) || S_ISCHR(mode))
		ft_putstr("\033[40;33;01m\033[1m");
	else if (S_ISFIFO(mode))
		ft_putstr("\033[40;33m");
	else if (mode & S_ISVTX)
		ft_putstr("\033[30;42m");
	else if (S_ISREG(mode))
	{
		if ((mode & S_IXUSR))
			ft_putstr("\033[0;32m\033[1m");
		else if ((mode & S_IXGRP))
			ft_putstr("\033[0;32m\033[1m");
		else if ((mode & S_IXUSR))
			ft_putstr("\033[0;32m\033[1m");
	}
}

void	display_name(t_item *items, t_args *args, int directory)
{
	if (args->options->color == 1 && directory == 0)
		set_color(items->stats->st_mode);
	if (args->options->q == 1)
		ft_putchar('"');
	ft_putstr(items->name);
	if (args->options->q == 1)
		ft_putchar('"');
	if (args->options->color == 1 && directory == 0)
		ft_putstr("\033[0m");
}
