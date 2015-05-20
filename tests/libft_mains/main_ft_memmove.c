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

        void *to_move;
        void *moved;
        void *src;


        src = memset(tab1, ft_atoi(av[2]), sizeof(int) * ft_atoi(av[1]));
        to_move = memset(tab2, ft_atoi(av[3]), sizeof(int) * ft_atoi(av[1]));

        printf("%p!=%p\n", src, to_move);
        moved = ft_memmove(tab2, tab1, ft_atoi(av[1]));
        printf("%p==%p", to_move, moved);

    return 0;
    }
}