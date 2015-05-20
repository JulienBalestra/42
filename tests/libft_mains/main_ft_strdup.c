#include "libft.h"
#include <string.h>
#include <stdlib.h>


int	main(int ac, char **av)
{
	int i;
	char *str1;
	char *str2;
	
	if (ac < 2)
	{
		return 1;
	}
	else
	{
		i = 0;
		while (i < ac)
		{
			str1 = strdup(av[i]);
			str2 = ft_strdup(av[i]);
			i++;
			if (strcmp(str1, str2) != 0)
			{
				free(str1);
				free(str2);
				return 2;
			free(str1);
            free(str2);
			}
		}
	}
	return 0;
}