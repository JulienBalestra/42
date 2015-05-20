#include "libft.h"

int	main(int ac, char **av)
{
	if (ac != 5)
	{
		return 1;
	}
	else
	{
	    int ret;
	    
		ret = ft_strnequ(av[1], av[2], (size_t) ft_atoi(av[3]));
		if (ret == ft_atoi(av[4]))
		    return 0;
	}
	return 2;
}