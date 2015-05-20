#include "libft.h"
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		return 1;
	}
	else
	{
		char *str1 = av[1];
		char *str2 = av[2];
		 
		int i = ft_strlcat(str1, str2, (size_t) ft_atoi(av[3]));
		printf("%i=", i);
		printf("%s:%s", str1, str2);

		
		
	}
	return 0;
}