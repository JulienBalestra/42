#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    else
    {
        int i = ft_atoi(av[1]);
        printf("%u", ft_absint(i));
        return 0;
    }
}