#include "ls.h"

int main(int ac, char **av)
{
    if (ac != 3)
        return (1);
    
    
    char    *path;
    size_t     len;
    
    len = ft_strlen(av[1]) + 1 + ft_strlen(av[2]); 
    path = ft_strnew(len);    
    ft_strncpy(path, av[1], ft_strlen(av[1]));
    ft_strncpy(&path[ft_strlen(av[1])], "/", 1);
    ft_strncpy(&path[ft_strlen(av[1]) + 1], av[2], ft_strlen(av[2]));
    ft_putstr(path);
    free(path);
    return (0);
}