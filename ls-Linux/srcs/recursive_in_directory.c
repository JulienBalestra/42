#include "ls.h"

static int		is_dot(char const *name)
{
	if (name[0] == '.' && name[1] == '\0')
		return (1);
	else if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (1);
	return (0);
}

void    recurse_in_directory(t_item *child_to_parent, t_args *args)
{
    DIR		*fd_file;
    
    fd_file = NULL;
    if (is_directory(child_to_parent) == 1 && is_dot(child_to_parent->name) == 0)
    {
        if ((fd_file = open_dir(child_to_parent->path)))
        {
            closedir(fd_file);
            ft_putchar('\n');
            args->options->Q ? ft_putchar('"') : 0;
            ft_putstr(child_to_parent->path);
            args->options->Q ? ft_putchar('"') : 0;
            ft_putstr(":\n");
            create_children(child_to_parent, args);
        }
        else 
            cannot_open(child_to_parent, args);
    }
}