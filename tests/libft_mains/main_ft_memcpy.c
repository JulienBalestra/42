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
        int *tab3;
        int *tab4;
        int i;
        tab1 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));
        tab2 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));
        tab3 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));
        tab4 = (int *) malloc(sizeof(int) * ft_atoi(av[1]));

        i = 0;
        memset(tab1, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        memset(tab2, ft_atoi(av[3]), sizeof(int) * ft_atoi(av[1]));
        ft_memset(tab3, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        ft_memset(tab4, ft_atoi(av[3]), sizeof(int) * ft_atoi(av[1]));
        memcpy(tab1, tab2, sizeof(int) * ft_atoi(av[1]));
        ft_memcpy(tab3, tab4, sizeof(int) * ft_atoi(av[1]));
        while (i < ft_atoi(av[1]))
        {
            printf("%i:%i ", tab1[i], tab3[i]);
            i++;
        }
    return 0;
    }
}