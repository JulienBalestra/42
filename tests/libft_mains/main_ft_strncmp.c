#include "libft.h"
#include <string.h>
#include <stdio.h>


int main(int ac, char **av)
{
    if (ac != 4)
        return 1;
    else
    {
        if (ft_strncmp(av[1], av[2], (size_t) ft_atoi(av[3])) != strncmp(av[1], av[2], (size_t) ft_atoi(av[3])))
        {
            printf("%i, %i", ft_strncmp(av[1], av[2], (size_t) ft_atoi(av[3])), strncmp(av[1], av[2], (size_t) ft_atoi(av[3])));
            return 2;
        }
    }
    return 0;
}