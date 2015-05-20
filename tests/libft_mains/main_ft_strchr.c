#include <string.h>
#include "libft.h"
#include <stdio.h>


int main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {
        printf("%s=%s", ft_strchr(av[1], av[2][0]), strchr(av[1], av[2][0]));
    }
    return 0;
}