#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    void *str;

    str = ft_memalloc((size_t)ft_atoi(av[1]));
    ft_memdel(&str);
    if (str)
        return 2;
    return 0;
}