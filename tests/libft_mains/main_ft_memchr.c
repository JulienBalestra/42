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

        tab1 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));

        memset(tab1, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        printf("%p==%p", memchr(tab1, ft_atoi(av[3]), sizeof(int) * ft_atoi(av[1])), ft_memchr(tab1, ft_atoi(av[3]), sizeof(int) * ft_atoi(av[1])));
    return 0;
    }
}