#include "libft.h"

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		return 1;
	}
	else
	{
	    int ret;

		ret = ft_strequ(av[1], av[2]);
		if (ret == ft_atoi(av[3]))
		    return 0;
	}
	return 2;
}