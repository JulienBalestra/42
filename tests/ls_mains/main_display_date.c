#include "ls.h"

int     main(int ac, char **av)
{
    if (ac < 1)
        return (1);
        
   t_ld    *ld;

    ld = create_ld();
    display_date(ft_atoi(av[1]), ld);
    return (0);
}
