/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:37:30 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:45:31 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			how_many_option(t_opt *options)
{
	int i;

	i = 0;
	(options->one == 1) ? i++ : 0;
	(options->l == 1) ? i++ : 0;
	(options->re == 1) ? i++ : 0;
	(options->a == 1) ? i++ : 0;
	(options->r == 1) ? i++ : 0;
	(options->t == 1) ? i++ : 0;
	(options->si == 1) ? i++ : 0;
	(options->q == 1) ? i++ : 0;
	(options->u == 1) ? i++ : 0;
	(options->f == 1) ? i++ : 0;
	(options->g == 1) ? i++ : 0;
	(options->d == 1) ? i++ : 0;
	(options->gr == 1) ? i++ : 0;
	(options->c == 1) ? i++ : 0;
	(options->color == 1) ? i++ : 0;
	return (i);
}

static int	match(char c)
{
	if (c == '1' || c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't'
		|| c == 'S' || c == 'U' || c == 'f' || c == 'g' || c == 'd'
			|| c == 'G' || c == 'C' || c == 'Q' || c == 'c')
		return (1);
	return (0);
}

static int	is_legal(char *av)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while (av[i] != '\0')
	{
		n = n + match(av[i]);
		i++;
	}
	return (i == n ? 1 : 0);
}

void		ft_get_options(t_args *args, char *av)
{
	if (args->options->f == 1)
		args->options->color = 0;
	else if (is_legal(av) == 1)
		find_options(args->options, av);
	else
		invalid_option(args, av);
}
