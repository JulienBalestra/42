#include "ls.h"

void	display_blank_for_digits(int use_case, int indent)
{
	int len;

	len = ft_nbrlen(use_case);
	while (len < indent)
	{
		ft_putchar(' ');
		len++;
	}
}

void	display_blank_for_str(int strlen, int indent, int Q)
{
	if (Q == 1)
		indent = indent - 2;
	/*ft_putnbr(strlen);
	ft_putstr("|");
	ft_putnbr(indent);*/
	while (strlen - 1 < indent - 2)
	{
		ft_putchar(' ');
		strlen++;
	}
	ft_putchar(' ');
	//ft_putstr("  ");
}