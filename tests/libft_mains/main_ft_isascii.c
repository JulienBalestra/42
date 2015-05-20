#include <ctype.h>
#include <stdio.h>

int	ft_isascii(char c);

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
				if ((isascii(av[i][n]) > 0) && (ft_isascii(av[i][n]) > 0))
                	n++;
                else if (isascii(av[i][n])== ft_isascii(av[i][n]))
                	n++;
				else
				{
					printf("%i:%i=%i\n", av[i][n], isascii(av[i][n]), ft_isascii(av[i][n]));
					return 2;
				}
			}
			n = 0;
			i++;
		}
	}
	if (isascii(128) != ft_isascii(128))
	{
    	printf("%i:%i=%i\n", 128, isascii(128), ft_isascii(128));
    	return 3;
    }
	return 0;
}
