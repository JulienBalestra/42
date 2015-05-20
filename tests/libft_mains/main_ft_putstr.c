#include "libft.h"

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
			ft_putstr(av[i]);
			i++;
		}
	}
	return 0;
}
