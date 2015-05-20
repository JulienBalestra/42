#include "ls.h"

void		verbose_invalid_option(char *av)
{
	ft_putstr_fd("ls: invalid option -- '", 2);
	ft_putchar_fd(get_illegal(av), 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd("Try 'ls --help' for more information.\n", 2);
}

void verbose_not_enough_memory(void)
{
	ft_putstr_fd("Not enough memory\n", 2);
	ft_putstr_fd("Please go get some\n", 2);
}