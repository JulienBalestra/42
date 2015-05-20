#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    int i;
    size_t mem_size;
    size_t n;
    char *str;
    
    i = 1;
    if (ac == i)
        return 1;
    else
    {
        while (i < ac)
        {
            n = 0;
            str = "toto";
            mem_size = ft_atoi(av[i]);
            str = ft_memalloc(mem_size);
            while (n < mem_size)
            {
                if (str[n] != '\0')
                    return 2;
                n++;
            }            
            i++;
        }
        
    }
    return 0;
}