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
    		printf("%i", ft_nbrlen(atoi(av[i])));
    		i++;
    	}
    }
	return 0;
}
