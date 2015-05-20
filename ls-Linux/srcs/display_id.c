#include "ls.h"

static void display_blank(int diff)
{
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
}

void	display_id(struct stat *stats, t_args *args)
{
	int diff;
	
	if (args->options->g == 0)
	{
		diff = 0;
		diff = args->ld->i_uid - (int)ft_strlen((getpwuid(stats->st_uid))->pw_name);
		ft_putstr((getpwuid(stats->st_uid))->pw_name);
		display_blank(diff);
		ft_putchar(' ');
	}
	
	if (args->options->G == 0)
	{
		diff = 0;
		diff = args->ld->i_gid - (int)ft_strlen(getgrgid(stats->st_gid)->gr_name);
		ft_putstr(getgrgid(stats->st_gid)->gr_name);
		display_blank(diff);
		ft_putchar(' ');
	}
}