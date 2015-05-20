#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		return 1;
	}
	else
	{
		char *str1 = av[1];
		if (strncpy(str1, av[2], atoi(av[3])) != ft_strncpy(av[1], av[2], atoi(av[3])))
			return 2;
		if (str1 != av[1])
			return 3;
	}
	return 0;
}