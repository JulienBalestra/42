#include <string.h>
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>


int main(int ac, char **av)
{
    if (ac != 4)
        return 1;
    else
    {
        printf("%s", ft_strnstr(av[1], av[2], atoi(av[3])));
    }
    return 0;
}