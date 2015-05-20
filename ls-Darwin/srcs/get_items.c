/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:36:00 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:36:54 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	from_args(t_args *args, char *str)
{
	t_item *file;

	file = NULL;
	args->inputs = args->inputs + 1;
	file = new_link(str, NULL, args);
	if (args->items)
		add_link(&(args->items), file, args->options->u);
	else
		args->items = file;
}

static void	default_args(t_args *args)
{
	t_item *file;

	file = new_link(".", NULL, args);
	args->items = file;
}

void		ft_get_items(t_args *args, char *str, int from_av)
{
	if (from_av == 1)
		from_args(args, str);
	else if (from_av == 0 && (args->items) == NULL)
		default_args(args);
}

int			browse_arguments_for_items(t_args *args, int opt, int ac, char **av)
{
	int i;
	int n;

	i = opt;
	n = opt;
	get_sorted_av(av, opt, ac);
	while (i < ac)
	{
		ft_get_items(args, av[i], 1);
		i++;
	}
	return (i - n);
}
