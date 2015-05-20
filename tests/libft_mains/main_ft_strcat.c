#include <string.h>
#include "libft.h"


int     main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {   
        if (strcmp(strcat(av[1], av[2]), (ft_strcat(av[1], av[2]))) != 0)
            return 2;
    }
    return 0;
}