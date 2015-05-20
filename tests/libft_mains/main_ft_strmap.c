#include "libft.h"
#include <stdio.h>


static char my_toupper(char s)
{
    return ft_toupper(s);
}


int	main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
	{
		return 1;
	}
	else
	{
		while (i < ac)
		{
			printf("%s", ft_strmap(av[i], my_toupper));
			i++;
		}
	}
	return 0;
}
