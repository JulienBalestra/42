/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:32:48 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:32:50 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	cannot_access(t_item *link, t_args *args)
{
	args->ret = 2;
	ft_putstr_fd("ls: ", 2);
	if (link->name[0] != '\0')
		ft_putstr_fd(link->name, 2);
	else
		ft_putstr_fd("fts_open", 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	destroy_link(link);
}

void	cannot_open(t_item *link, t_args *args)
{
	args->ret = 2;
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(link->path, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
}

char	get_illegal(char *av)
{
	int	i;

	i = 1;
	while (av[i] != '\0')
	{
		if (av[i] == 'l' || av[i] == 'R' || av[i] == 'a' || av[i] == 'r'
			|| av[i] == 't' || av[i] == 'u' || av[i] == 'f' || av[i] == 'g' ||
			av[i] == 'd' || av[i] == 'G')
			i++;
		else
			return (av[i]);
	}
	return ('\0');
}

void	invalid_option(t_args *args, char *av)
{
	verbose_invalid_option(av);
	clean_program(&args);
	_exit(2);
}

void	not_enough_memory(t_args *args)
{
	verbose_not_enough_memory();
	if (args != NULL)
		clean_program(&args);
	_exit(2);
}
