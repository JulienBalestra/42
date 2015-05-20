/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hard_link.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:13:19 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:15:53 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			display_hard_link(nlink_t st_nlink, int i_nlink)
{
	display_blank_for_digits((int)st_nlink, i_nlink);
	ft_putnbr(st_nlink);
	ft_putchar(' ');
}

static void		display_color_slink(char *s_buf, t_args *args)
{
	struct stat	*slink;

	slink = NULL;
	if (args->options->color == 1 &&
			(slink = (struct stat *)malloc(sizeof(struct stat))))
	{
		if (stat(s_buf, slink) == 0)
		{
			set_color(slink->st_mode);
		}
		free(slink);
		slink = NULL;
	}
}

static char		*get_relative_path(char *buf, t_item *items)
{
	char	*path;
	int		l_prt;
	int		l_buf;

	path = NULL;
	l_prt = 0;
	l_buf = 0;
	if (buf && items->parent && !(ft_strchr(buf, '/')))
	{
		l_prt = ft_strlen(items->parent->path);
		l_buf = ft_strlen(buf);
		if (((path = (char *)malloc(sizeof(char) * (l_prt + l_buf + 2)))))
		{
			ft_strncpy(path, items->parent->path, l_prt);
			ft_strncpy(&path[l_prt], "/", 1);
			ft_strncpy(&path[l_prt + 1], buf, l_buf);
			path[l_prt + l_buf + 1] = '\0';
		}
	}
	return (path);
}

static void		display_with_color(char *buf, t_item *items, t_args *args)
{
	char	*path;

	path = NULL;
	path = get_relative_path(buf, items);
	if (path)
	{
		display_color_slink(path, args);
		free(path);
	}
	else
		display_color_slink(buf, args);
	args->options->q == 1 ? ft_putchar('"') : 0;
	ft_putstr(buf);
	args->options->q == 1 ? ft_putchar('"') : 0;
	ft_putstr("\033[0m");
}

void			display_symbolic_link(t_item *items, t_args *args)
{
	char	buf[1024];
	int		ret;

	ret = 0;
	if (S_ISLNK(items->stats->st_mode))
	{
		if ((ret = readlink(items->path, buf, 1024)))
		{
			ft_putstr(" -> ");
			buf[ret] = '\0';
			if (args->options->q == 0 && args->options->color == 0)
				ft_putstr(buf);
			else
				display_with_color(buf, items, args);
		}
	}
}
