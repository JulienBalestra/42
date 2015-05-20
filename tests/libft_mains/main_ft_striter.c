#include "libft.h"


static void my_putstr(char *s)
{
    ft_putchar(s[0]);
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
			ft_striter(av[i], my_putstr);
			i++;
		}
	}
	return 0;
}
