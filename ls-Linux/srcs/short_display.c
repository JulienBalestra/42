#include "ls.h"

static void	child_display(t_item *items, t_args *args)
{
	t_item	*child;
	int		ret;
	
	ret = 1;
	child = items->child;
	child = merge_sort_list_recursive(child, args);
	if (args->options->C == 1)
	{
		iter_for_len(child, args, 0);
		ret = run_matrix(args, child, 0);
	}
	if (ret == 1)
	{
		while (child)
		{
			display_name(child, args, 0);
			ft_putchar('\n');
			child = child->next;
		}
	}
}

void	file_display(t_item *items, t_args *args)
{
	int		ret;
	
	ret = 1;
	if (args->options->C == 1)
	{
		iter_for_len(items, args, 0);
		ret = run_matrix(args, items, 0);
	}
	if (ret == 1)
	{
		while (items)
		{
			if (items->child == NULL)
			{
				display_name(items, args, 0);
				ft_putchar('\n');
			}
			items = items->next;
		}
	}
	items = get_start(items);
}

static void directory_display(t_item *items, t_args *args)
{
	while (items)
	{
		if (items->child)
		{
			if (items->prev)
				ft_putchar('\n');
			if (items->next || items->prev)
			{
				display_name(items, args, 1);
				ft_putstr(":\n");
			}
			child_display(items, args);
		}
		items = items->next;
	}
}

void	short_display(t_item *items, t_args *args)
{
	items = get_start(items);
	items = merge_sort_list_recursive(items, args);
	file_display(items, args);
	directory_display(items, args);
}