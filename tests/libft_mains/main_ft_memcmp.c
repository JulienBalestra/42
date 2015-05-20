#include <string.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>


int main (int ac, char **av)
{
    if (ac != 4)
        return 1;
    else
    {
        int *tab1;
        int *tab2;

        tab1 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));
        tab2 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));

        ft_memset(tab1, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        ft_memset(tab2, ft_atoi(av[3]), sizeof(int) * ft_atoi(av[1]));

        printf("%i==%i", ft_memcmp(tab1, tab2, sizeof(int) * ft_atoi(av[1])), memcmp(tab1, tab2, sizeof(int) * ft_atoi(av[1])));




    return 0;
    }
}