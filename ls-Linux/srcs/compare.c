#include "ls.h"

int	compare_name(t_item *one, t_item *two, int reverse)
{
	int i;

	i = 0;
	while ((one->name[i] != '\0') && (two->name[i] != '\0') && (one->name[i] == two->name[i]))
		i++;
	if (one->name[i] - two->name[i] < 0)
		return (reverse ? 0 : 1);
	return (reverse ? 1 : 0);
}

int	compare_mtime(t_item *one, t_item *two, int reverse)
{
	if (one->stats->st_mtime == two->stats->st_mtime)
	{
		if (one->stats->st_ino > two->stats->st_ino)
			return (reverse ? 0 : 1);
		else
			return (reverse ? 1 : 0);
	}
	if (one->stats->st_mtime > two->stats->st_mtime)
		return (reverse ? 0 : 1);
	return (reverse ? 1 : 0);
}

int	compare_size(t_item *one, t_item *two, int reverse)
{
	if (one->stats->st_size == two->stats->st_size)
		return (compare_name(one, two, reverse));
	if (one->stats->st_size > two->stats->st_size)
		return (reverse ? 0 : 1);
	return (reverse ? 1 : 0);
}

int	do_nothing(t_item *one, t_item *two, int reverse)
{
	(void)one;
	(void)two;
	(void)reverse;
	return (0);
}

void	choose_pivot(t_args *args)
{
	if (args->options->t == 1)
		args->compare = compare_mtime;
	else if (args->options->S == 1)
		args->compare = compare_size;
	else
		args->compare = compare_name;
	if (args->options->U)
		args->compare = do_nothing;
}