#include "ls.h"

static void	set_options(t_opt *options)
{
	if (options)
	{
		options->one = 0;
		options->l = 0;
		options->R = 0;
		options->a = 0;
		options->r = 0;
		options->t = 0;
		options->S = 0;
		options->Q = 0;
		options->U = 0;
		options->f = 0;
		options->g = 0;
		options->d = 0;
		options->G = 0;
		options->C = 0;
		options->color = 0;
	}
}

static void browse_arguments_for_options(t_args *args, int ac, char ** av)
{
	int i;
	
	i = 1;
	while (i < ac)
	{
		if (!(av[i][0] == '-' && av[i][1] == '-' && av[i][2] == '\0') && av[i][0] == '-')
			ft_get_options(args, av[i]);
		i++;
	}
}

int browse_arguments_for_items(t_args *args, int ac, char **av)
{
	int i;
	int n;
	
	i = 1;
	n = 0;
	while (i < ac)
	{
		if ((av[i][0] == '-' && av[i][1] == '\0') || av[i][0] != '-')
		{
			ft_get_items(args, av[i], 1);
			n++;
		}
		i++;
	}
	return (n);
}

static void set_t_args(t_args *args, char **av)
{
	set_options(args->options);
	args->ret = 0;
	args->items = NULL;
	args->program = av[0];
	args->compare = NULL;
}

t_args *ft_get_args(int ac, char **av)
{
	t_args *args;
	
	args = NULL;
	if ((args = (t_args *)malloc(sizeof(t_args))) &&
			(args->options = (t_opt *)malloc(sizeof(t_opt))) && 
				(args->ld = create_ld()) &&
					(args->sd = create_sd_props()))
	{
		set_t_args(args, av);
		browse_arguments_for_options(args, ac, av);
		choose_pivot(args);
		if (args->options->C == 1 && args->options->l == 0)
			args->sd_ts = get_columns();
		if (args->options->R == 1)
			recurse_browse_arguments_for_items(args, ac, av);
		else if (browse_arguments_for_items(args, ac, av) == 0)
			ft_get_items(args, NULL, 0);
	}
	else
		not_enough_memory(NULL);
	return (args);
}