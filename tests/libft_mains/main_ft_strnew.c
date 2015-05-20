#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    size_t mem_size;
    char *str;
    size_t i;

    if (ac != 3)
        return 1;
    else
    {
        mem_size = ft_atoi(av[1]);
        str = ft_strnew(mem_size);
        strcpy(str, av[2]);
        i = 0;
        while (i < mem_size)
        {
            if (str[i] != av[2][i])
                return 2;
            i++;
        }
    }
    return 0;
}