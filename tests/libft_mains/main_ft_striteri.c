#include "libft.h"
#include <stdio.h>


static void my_putstr(unsigned int i, char *s)
{
	ft_putnbr((int) i);
	ft_putchar(*s);
}


int	main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
	{
		return 1;
	}
	else
	{
		while (i < ac)
		{
			ft_striteri(av[i], my_putstr);
			i++;
		}
	}
	return 0;
}
