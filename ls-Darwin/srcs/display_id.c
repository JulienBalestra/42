/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:16:23 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:20:19 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	display_blank(int diff)
{
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
}

void		putuid(int uid, int pw)
{
	if (pw == 1)
	{
		if (getpwuid(uid))
			ft_putstr(getpwuid(uid)->pw_name);
		else
			ft_putnbr(uid);
	}
	else
	{
		if (getgrgid(uid))
			ft_putstr(getgrgid(uid)->gr_name);
		else
			ft_putnbr(uid);
	}
}

int			uidlen(int uid, int pw)
{
	if (pw == 1)
	{
		if (getpwuid(uid))
			return (ft_strlen(getpwuid(uid)->pw_name));
		else
			return (ft_nbrlen(uid));
	}
	else
	{
		if (getgrgid(uid))
			return (ft_strlen(getgrgid(uid)->gr_name));
		else
			return (ft_nbrlen(uid));
	}
}

void		display_id(struct stat *stats, t_args *args)
{
	int diff;

	diff = 0;
	if (args->options->g == 0)
	{
		diff = 0;
		diff = args->ld->i_uid - uidlen(stats->st_uid, 1);
		putuid(stats->st_uid, 1);
		display_blank(diff);
		ft_putstr("  ");
	}
	if (args->options->gr == 0)
	{
		diff = 0;
		diff = args->ld->i_gid - uidlen(stats->st_gid, 0);
		putuid(stats->st_gid, 0);
		display_blank(diff);
		if (args->ld->i_gid == 11 && args->ld->i_major == 0 &&
				args->ld->i_minor == 0)
			return ;
		ft_putstr("  ");
	}
}
