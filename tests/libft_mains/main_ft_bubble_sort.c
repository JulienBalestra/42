#include "libft.h"
#include <string.h>


int main(int ac, char **av)
{
    int i;
    
    i = 1;
    if (ac == 1)
        return 1;
    else
    {
        ft_bubble_sort(av, 1, ac);        
        while (i < ac)
        {
            ft_putstr(av[i]);
            ft_putchar(',');
            i++;
        }
    }
    return 0;
}