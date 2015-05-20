#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    size_t mem_size;
    char *str;


    if (ac != 3)
        return 1;
    else
    {
        mem_size = ft_atoi(av[1]);
        str = ft_strnew(mem_size);
        strcpy(str, av[2]);
        ft_strdel(&str);
        if (str != NULL)
            return 2;
    }
    return 0;
}