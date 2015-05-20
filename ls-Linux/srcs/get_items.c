#include "ls.h"

static void from_args(t_args *args, char *str)
{
	t_item *file;

	file = NULL;
	file = new_link(str, NULL, args);
	if (args->items)
		add_link(&(args->items), file, args->options->U);
	else
		args->items = file;
}

static void default_args(t_args *args)
{
	t_item *file;
	
	file = new_link(".", NULL, args);
	args->items = file;
}

void	ft_get_items(t_args *args, char *str, int from_av)
{
	if (from_av == 1)
		from_args(args, str);
	else if (from_av == 0 && (args->items) == NULL)
		default_args(args);
}

void		replay_directory(t_item *items, t_args *args)
{
	t_item 	*start;
	int		i;
	
	start = NULL;
	start = get_start(items);
	i = 0;
	while (items)
	{
		if (items->child)
		{
			if (i == 1)
				ft_putchar('\n');
			ft_get_items(args, items->name, 1);
			i = 1;
		}
		items = items->next;
	}
	del_list(&start, 0);
}

void	display_endline(t_item *items)
{
	t_item	*tmp;
	int i;
	
	tmp = NULL;
	tmp = items;
	i = 0;
	while (tmp)
	{
		if (tmp->child == NULL)
			i = 1;
		tmp = tmp->next;
	}
	if (i == 1)
		ft_putchar('\n');
}

void	recurse_browse_arguments_for_items(t_args *args, int ac, char **av)
{
	t_item *tmp;
	
	tmp = NULL;
	args->options->R = 0;
	if (browse_arguments_for_items(args, ac, av) == 0)
	{
		args->options->R = 1;
		ft_get_items(args, NULL, 0);
	}
	else
	{		
		tmp = merge_sort_list_recursive(args->items, args);
		args->items = NULL;
		if (args->options->l == 1)
			display_file_only(tmp, args);
		else
			file_display(tmp, args);
		display_endline(tmp);
		args->options->R = 1;
		replay_directory(tmp, args);
	}
}