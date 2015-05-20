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
		while (i < ac)
		{
			while (av[i][n] != '\0')
			{
				if ((isdigit(av[i][n]) > 0) && (ft_isdigit(av[i][n]) > 0))
                                	n++;
                                else if (isdigit(av[i][n]) == ft_isdigit(av[i][n]))
                                	n++;
				else
				{
					printf("%i:%i=%i\n", av[i][n], isdigit(av[i][n]), ft_isdigit(av[i][n]));
					return 2;
				}
			}
			n = 0;
			i++;
		}
	}
	return 0;
}