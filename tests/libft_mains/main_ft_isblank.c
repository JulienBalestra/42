#include <ctype.h>
#include <stdio.h>

int	ft_isblank(char c);

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
				if (isblank(av[i][n]) == ft_isblank(av[i][n]))
					n++;
				else
				{
					printf("%i:%i=%i\n", av[i][n], isblank(av[i][n]), ft_isblank(av[i][n]));
					return 2;
				}
			}
			n = 0;
			i++;
		}
	}
	return 0;
}
