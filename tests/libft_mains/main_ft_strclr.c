#include "libft.h"
#include <stdio.h>

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
			ft_strclr(av[i]);
			printf("%s", av[i]);
			i++;
		}
	}
	return 0;
}
