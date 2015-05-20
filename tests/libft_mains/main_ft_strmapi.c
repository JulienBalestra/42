#include "libft.h"
#include <stdio.h>


static char my_toupper(unsigned int i, char s)
{
	(void)i;
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
			printf("%s", ft_strmapi(av[i], my_toupper));
			i++;
		}
	}
	return 0;
}
