/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_in_directory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:35:57 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:41:06 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	is_dot(char const *name)
{
	if (name[0] == '.' && name[1] == '\0')
		return (1);
	else if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (1);
	return (0);
}

static void failed_open_dir(t_item *child_to_parent, t_args *args)
{
	ft_putchar('\n');
	if (args->options->q)
		ft_putchar('"');
	ft_putstr(child_to_parent->path);
	if (args->options->q)
		ft_putchar('"');
	ft_putstr(":\n");
	cannot_open(child_to_parent, args);
}

void		recurse_in_directory(t_item *child_to_parent, t_args *args)
{
	DIR	*fd_file;

	fd_file = NULL;
	if (is_directory(child_to_parent) && is_dot(child_to_parent->name) == 0)
	{
		if ((fd_file = open_dir(child_to_parent->path)))
		{
			closedir(fd_file);
			ft_putchar('\n');
			if (args->options->q)
				ft_putchar('"');
			ft_putstr(child_to_parent->path);
			if (args->options->q)
				ft_putchar('"');
			ft_putstr(":\n");
			create_children(child_to_parent, args);
		}
		else
		{
			failed_open_dir(child_to_parent, args);
		}
	}
}
