#include "ls.h"

void	selected_print(t_item *items, t_args *args)
{
	display_protection(items->stats->st_mode, items->path);
	display_hard_link(items->stats->st_nlink, args->ld->i_nlink);
	display_id(items->stats, args);
	display_dev_or_size(items->stats, args->ld);
	display_date(items->stats->st_mtime, args->ld);
	display_name(items, args, 0);
	display_symbolic_link(items, args);
	ft_putchar('\n');
}

void	iter_on_links(t_item *items, t_ld *ld, int file_only)
{
	t_item	*start;

	set_ld(ld);
	items = get_start(items);
	start = items;
	while (items)
	{
		if (file_only && items->child == NULL)
			get_ld(items->stats, ld);
		else if (file_only == 0)
			get_ld(items->stats, ld);
		items = items->next;
	}
	items = start;
}

void	display_total_blocks(int total_blocks)
{
	ft_putstr("total ");
	ft_putnbr(total_blocks);
	ft_putchar('\n');
}

static void	display_child(t_item *items, t_args *args)
{
	t_item	*child;
	
	child = items->child;
	iter_on_links(child, args->ld, 0);
	display_total_blocks(args->ld->total_blocks);
	while (child)
	{
		selected_print(child, args);
		child = child->next;
	}
}

void	display_file_only(t_item *items, t_args *args)
{
	t_item	*start;
	
	start = items;
	iter_on_links(items, args->ld, 1);
	while (items)
	{
		if (items->child == NULL)
			selected_print(items, args);
		items = items->next;
	}
	items = start;
}

static void browse_directory_to_display(t_item *items, t_args *args)
{
	while (items)
	{
		if (items->child)
		{
			if (items->prev)
				ft_putchar('\n');
			if (items->next || items->prev)
			{
				args->options->Q == 1 ? ft_putchar('"') : 0;
				ft_putstr(items->name);
				args->options->Q == 1 ? ft_putchar('"') : 0;
				ft_putstr(":\n");
			}
			display_child(items, args);
		}
		items = items->next;
	}
}

void	long_display(t_item *items, t_args *args)
{
	items = merge_sort_list_recursive(items, args);
	display_file_only(items, args);
	browse_directory_to_display(items, args);
}