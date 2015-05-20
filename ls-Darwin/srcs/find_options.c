/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:45:54 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:47:41 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void first_bloc(t_opt *options, char *av)
{
	while (*av != '\0')
	{
		(*av == '1') ? (options->one = 1) : 0;
		(*av == '1') ? (options->c = 0) : 0;
		(*av == 'l') ? (options->l = 1) : 0;
		(*av == 'R') ? (options->re = 1) : 0;
		(*av == 'a') ? (options->a = 1) : 0;
		(*av == 'r') ? (options->r = 1) : 0;
		(*av == 't') ? (options->t = 1) : 0;
		(*av == 't') ? (options->si = 0) : 0;
		(*av == 'S') ? (options->si = 1) : 0;
		(*av == 'S') ? (options->t = 0) : 0;
		(*av == 'Q') ? (options->q = 1) : 0;
		(*av == 'U') ? (options->u = 1) : 0;
		av++;
	}
}

static void second_bloc(t_opt *options, char *av)
{
	while (*av != '\0')
	{
		(*av == 'f') ? (options->f = 1) : 0;
		(*av == 'f') ? (options->u = 1) : 0;
		(*av == 'f') ? (options->a = 1) : 0;
		(*av == 'f') ? (options->color = 0) : 0;
		(*av == 'g') ? (options->g = 1) : 0;
		(*av == 'd') ? (options->d = 1) : 0;
		(*av == 'G') ? (options->gr = 1) : 0;
		(*av == 'C') ? (options->c = 1) : 0;
		(*av == 'C') ? (options->one = 0) : 0;
		(*av == 'c') ? (options->color = 1) : 0;
		av++;
	}
}

void		find_options(t_opt *options, char *av)
{
	first_bloc(options, av);
	second_bloc(options, av);
}
