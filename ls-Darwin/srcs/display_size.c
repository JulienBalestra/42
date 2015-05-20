/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 18:11:21 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/12 18:13:53 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		display_major_minor(dev_t dev, int i_major, int i_minor)
{
	int			major_nb;
	int			minor_nb;

	major_nb = 0;
	minor_nb = 0;
	major_nb = major(dev);
	minor_nb = minor(dev);
	ft_putchar(' ');
	display_blank_for_digits(major_nb, i_major);
	ft_putnbr(major_nb);
	ft_putchar(',');
	display_blank_for_digits(minor_nb, i_minor);
	ft_putnbr(minor_nb);
	ft_putchar(' ');
}

static void		display_size(off_t size, int i_size)
{
	display_blank_for_digits((int)size, i_size);
	ft_putnbr(size);
	ft_putchar(' ');
}

void			display_dev_or_size(struct stat *stats, t_ld *ld)
{
	if (S_ISBLK(stats->st_mode) || S_ISCHR(stats->st_mode))
		display_major_minor(stats->st_rdev, ld->i_major, ld->i_size);
	else
	{
		if (ld->i_major)
		{
			ft_putchar(' ');
			display_blank_for_digits(0, ld->i_major);
			ft_putstr("  ");
		}
		display_size(stats->st_size, ld->i_size);
	}
}
