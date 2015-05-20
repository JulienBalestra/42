#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    char *str1;

    if (ac != 2)
        return 1;
    else
    {
        int i = ft_atoi(av[1]);
        str1 = ft_itoa(i);
        if (strcmp(av[1], str1) != 0)
            return 2;
    }
    return 0;
}