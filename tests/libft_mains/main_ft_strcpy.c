#include "libft.h"
#include <string.h>


int	main(int ac, char **av)
{
	if (ac != 3)
	{
		return 1;
	}
	else
	{
		char *str1 = av[1];
		if (strcpy(str1, av[2]) != ft_strcpy(av[1], av[2]))
			return 2;
		if (str1 != av[1])
			return 3;
	}
	return 0;
}