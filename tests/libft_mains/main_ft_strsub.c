#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    char *str1;

    if (ac != 5)
        return 1;
    else
    {
        str1 = ft_strsub((char const *) av[1], (unsigned int) ft_atoi(av[2]), (size_t) ft_atoi(av[3]));
        int i = 0;
        while (i < ft_atoi(av[3]))
        {
            if (str1[i] != av[4][i])
                return 2;
            i++;
        }
    }
    return 0;
}