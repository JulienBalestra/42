/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:33:24 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:35:44 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	set_options(t_opt *options)
{
	if (options)
	{
		options->one = 0;
		options->l = 0;
		options->re = 0;
		options->a = 0;
		options->r = 0;
		options->t = 0;
		options->si = 0;
		options->q = 0;
		options->u = 0;
		options->f = 0;
		options->g = 0;
		options->d = 0;
		options->gr = 0;
		options->c = 0;
		options->color = 0;
	}
}

static int	browse_arguments_for_options(t_args *args, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] == '-' && av[i][2] == '\0')
		{
			i++;
			break ;
		}
		else if (av[i][0] == '-' && av[i][1] != '\0')
		{
			ft_get_options(args, av[i]);
			i++;
		}
		else
			break ;
	}
	return (i);
}

static void	set_t_args(t_args *args)
{
	set_options(args->options);
	args->ret = 0;
	args->inputs = 0;
	args->items = NULL;
	args->compare = NULL;
}

t_args		*ft_get_args(int ac, char **av)
{
	t_args	*args;
	int		opt;

	args = NULL;
	opt = 0;
	if ((args = (t_args *)malloc(sizeof(t_args))) &&
			(args->options = (t_opt *)malloc(sizeof(t_opt))) &&
				(args->ld = create_ld()) &&
					(args->sd = create_sd_props()))
	{
		set_t_args(args);
		opt = browse_arguments_for_options(args, ac, av);
		choose_pivot(args);
		if (args->options->c == 1 && args->options->l == 0)
			args->sd_ts = get_columns();
		if (args->options->re == 1)
			recurse_browse_arguments_for_items(args, opt, ac, av);
		else if (browse_arguments_for_items(args, opt, ac, av) == 0)
			ft_get_items(args, NULL, 0);
	}
	else
		not_enough_memory(NULL);
	return (args);
}
