#include <string.h>
#include "libft.h"
#include <stdio.h>


int main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {
        printf("%s", ft_strcasestr(av[1], av[2]));
    }
    return 0;
}