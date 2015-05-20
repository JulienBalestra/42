#include "libft.h"
#include <string.h>
#include <stdio.h>


int     main(int ac, char **av)
{
    char *str1;
    char *str2;
    char *str3;
    

    if (ac != 4)
        return 1;
    else
    {
        str1 = av[1];
        str2 = av[2];
        str3 = ft_strjoin(str1, str2);
        size_t i = 0;
        while (i < ft_strlen(av[3]))
        {
            if (str3[i] != av[3][i])
                return 2;
            i++;
        }
    }
    return 0;
}