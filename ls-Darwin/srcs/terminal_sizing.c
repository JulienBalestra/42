/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_sizing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:01:38 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:06:51 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			get_columns(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

static void	get_max_len(t_item *items, t_args *args)
{
	int len;

	len = 0;
	len = ft_strlen(items->name);
	if (args->options->q == 1 && len > 0)
		len = len + 2;
	if (len > args->sd->len_items)
		args->sd->len_items = len;
}

t_sd		*create_sd_props(void)
{
	t_sd	*sd;

	sd = NULL;
	if ((sd = (t_sd *)malloc(sizeof(t_sd))))
	{
		sd->len_items = 0;
		sd->nb_items = 0;
	}
	return (sd);
}

static void set_sd_props(t_args *args)
{
	args->sd->len_items = 0;
	args->sd->nb_items = 0;
	args->sd->nb_col = 0;
	args->sd->nb_lines = 0;
}

void		iter_for_len(t_item *items, t_args *args, int directory)
{
	t_item *start;

	start = NULL;
	set_sd_props(args);
	if (items)
	{
		start = get_start(items);
		while (items)
		{
			if (directory == 0 && items->child == NULL)
			{
				get_max_len(items, args);
				args->sd->nb_items++;
			}
			else
			{
				get_max_len(items, args);
				args->sd->nb_items++;
			}
			items = items->next;
		}
		items = start;
		start = NULL;
	}
}
