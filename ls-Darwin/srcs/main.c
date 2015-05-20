/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:02:53 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:03:23 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int ac, char **av)
{
	t_args	*args;
	int		ret;
	t_item	*items;

	args = NULL;
	ret = 0;
	items = NULL;
	args = ft_get_args(ac, av);
	items = get_start(args->items);
	if (args->options->re == 0)
		args->options->l ? long_display(items, args)
			: short_display(items, args);
	ret = args->ret;
	clean_program(&args);
	return (ret);
}
