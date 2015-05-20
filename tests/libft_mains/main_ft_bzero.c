#include <string.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>


int main (int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {
        int *tab1;
        int *tab2;
        int i;
        tab1 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));
        tab2 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));

        i = 0;
        memset(tab1, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        ft_memset(tab2, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        bzero(tab1, sizeof(int) * ft_atoi(av[1]));
        ft_bzero(tab2, sizeof(int) * ft_atoi(av[1]));
        i = 0;
        while (i < ft_atoi(av[1]))
        {
            printf("%i:%i ", tab1[i], tab2[i]);
            i++;
        }
    return 0;
    }
}