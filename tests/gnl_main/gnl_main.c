#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "get_next_line.h"
#include "libft.h"


int main(int ac, char **av)
{
    int fd;
    int ret;
    char *line;
    
    (void)ac;
    fd = open(av[1], O_RDONLY);

    while((ret = get_next_line(fd, &line)) == 1)
    {
        ft_putnbr(ret);
        ft_putstr(":");
        ft_putstr(line);
        ft_putstr(",");
    }
    ft_putnbr(ret);
    close(fd);
    if (line)
        return(-1);
    return 0;
}