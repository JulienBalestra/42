#include <string.h>
#include <stdio.h>
#include "libft.h"


int     main(int ac, char **av)
{
    if (ac != 4)
        return 1;
    else
    {
        if (strcmp(strncat(av[1], av[2], ft_atoi(av[3])), (ft_strncat(av[1], av[2], ft_atoi(av[3])))) != 0)
            return 2;
    }
    return 0;
}