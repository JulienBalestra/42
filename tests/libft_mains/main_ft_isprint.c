#include <ctype.h>
#include "libft.h"
#include <stdio.h>

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
				if ((isprint(av[i][n]) > 0) && (ft_isprint(av[i][n]) > 0))
					n++;
                else if (isprint(av[i][n]) == ft_isprint(av[i][n]))
					n++;
				else
				{
					printf("%i:%i=%i\n", av[i][n], isprint(av[i][n]), ft_isprint(av[i][n]));
					return 2;
				}
			}
			n = 0;
			i++;
		}
	}
	//printf("%i:%i\n", isprint('a'), ft_isprint('a'));
	return 0;
}
