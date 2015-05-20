#include <ctype.h>
#include <stdio.h>
#include "libft.h"


int	main(int ac, char **av)
{
	int i;
	int n;

	if (ac == 1)
		return 1;
	else
	{
		i = 1;
		n = 0;
		while (i < ac)
		{
			while (av[i][n] != '\0')
			{
				if (toupper(av[i][n]) == ft_toupper(av[i][n]))
					n++;
				else
				{
					printf("%i:%i=%i\n", av[i][n], toupper(av[i][n]), ft_toupper(av[i][n]));
					return 2;
				}
			}
			i++;
		}
	}
	return 0;
}