#include <stdlib.h>
#include <stdio.h>
#include "libft.h"


int	main(int ac, char **av)
{
	int i;

	if (ac == 1)
		return 1;
	else
	{
		i = 1;
		while (i < ac)
		{
			if (atoi(av[i]) == ft_atoi(av[i]))
				i++;
			else
			{
				printf("%s:%i=%i\n", av[i], atoi(av[i]), ft_atoi(av[i]));
				return 2;
			}
			
		}
	}
	return 0;
}
