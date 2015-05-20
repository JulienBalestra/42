/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:06:05 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:09:49 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char	*get_path(t_item *link)
{
	char	*path;
	int		len_parent;
	int		len_name;

	len_parent = ft_strlen(link->parent->path);
	len_name = ft_strlen(link->name);
	path = NULL;
	if ((path = (char *)malloc(sizeof(char) * (len_parent + len_name + 2))))
	{
		ft_strncpy(path, link->parent->path, len_parent);
		ft_strncpy(&path[len_parent], "/", 1);
		len_parent++;
		ft_strncpy(&path[len_parent], link->name, len_name);
		path[len_parent + len_name] = '\0';
	}
	return (path);
}

static int	build_stats(t_item *link, t_args *args)
{
	int	ret;

	ret = 2;
	link->stats = NULL;
	if ((link->stats = (struct stat *)malloc(sizeof(struct stat))))
	{
		if (args->options->l == 1 || args->options->t == 1 ||
				args->options->re == 1)
		{
			if ((ret = lstat(link->path, link->stats)) != 0)
				cannot_access(link, args);
		}
		else
		{
			if ((ret = stat(link->path, link->stats)) != 0)
			{
				if ((ret = lstat(link->path, link->stats)) != 0)
					cannot_access(link, args);
			}
		}
	}
	else
		not_enough_memory(args);
	return (ret);
}

static void	set_new_link(t_item *link)
{
	if (link)
	{
		link->name = NULL;
		link->path = NULL;
		link->next = NULL;
		link->prev = NULL;
		link->parent = NULL;
		link->child = NULL;
	}
}

t_item		*new_link(char const *name, t_item *parent, t_args *args)
{
	t_item	*link;

	link = NULL;
	if ((link = (t_item *)malloc(sizeof(t_item))))
	{
		set_new_link(link);
		link->name = ft_strdup(name);
		link->parent = (t_item *)parent;
		if (link->parent)
			link->path = get_path(link);
		else
			link->path = link->name;
		if (build_stats(link, args) != 0)
			return (NULL);
		if (parent == NULL && ((args->options->l == 1 &&
				is_symbolic_link(link) == 0) || (args->options->l == 0)))
			create_children(link, args);
	}
	else
		not_enough_memory(args);
	return (link);
}

void		add_link(t_item **alist, t_item *new_link, int end)
{
	if (*alist && new_link)
	{
		if (end == 0)
		{
			if ((*alist)->prev)
				*alist = get_start(*alist);
			new_link->next = *alist;
			(*alist)->prev = new_link;
			*alist = new_link;
		}
		else
		{
			if ((*alist)->next)
				*alist = get_end(*alist);
			new_link->prev = *alist;
			(*alist)->next = new_link;
			*alist = get_start(new_link);
		}
	}
}
