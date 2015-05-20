#include <ctype.h>
#include <stdio.h>

int	ft_isalnum(char c);

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
				if ((isalnum(av[i][n]) > 0) && (ft_isalnum(av[i][n]) > 0))
					n++;
				else if (isalnum(av[i][n])== ft_isalnum(av[i][n]))
					n++;
				else
				{
					printf("%i:%i=%i\n", av[i][n], isalnum(av[i][n]), ft_isalnum(av[i][n]));
					return 2;
				}
			}
			n = 0;
			i++;
		}
	}
	return 0;
}
