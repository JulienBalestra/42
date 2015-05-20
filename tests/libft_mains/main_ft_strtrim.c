#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    char *str1;

    if (ac != 3)
        return 1;
    else
    {
        str1 = ft_strtrim((char const *) av[1]);
        if (strcmp(str1, av[2]) != 0)
        {
            printf("%s:%s\n", str1, av[2]);
            return 2;
        }
    }
    return 0;
}