#include "libft.h"
#include <string.h>


int main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {
        if (ft_strcmp(av[1], av[2]) != strcmp(av[1], av[2]))
            return 2;
    }
    return 0;
}