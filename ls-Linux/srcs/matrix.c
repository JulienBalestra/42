#include "ls.h"

static void     set_matrix_size(t_sd *sd, int sd_ts)
{
    sd->len_items = sd->len_items + 2;
    if (sd->len_items > sd_ts)
        sd->nb_col = 1;
    else
        sd->nb_col = min(sd->nb_items, (sd_ts / sd->len_items));
    sd->nb_lines = round_up(sd->nb_items, sd->nb_col) + 1;
}

static t_item   ***create_matrix(t_sd *sd)
{
    t_item      ***matrix;
    t_item      **line;
    int         l;
    int         c;
    
    matrix = NULL;
    line = NULL;
    l = 0;
    c = 0;
    if ((matrix = (t_item ***)malloc(sizeof(t_item ***) * (sd->nb_lines + 1))))
    {   
        while (l < sd->nb_lines)
        {
            if ((line = (t_item **)malloc(sizeof(t_item **) * (sd->nb_col + 1))))
            {
                c = 0;
                while (c < sd->nb_col)
                {
                    line[c] = NULL;
                    c++;
                }
                matrix[l] = line;
            }
            l++;
        }
        matrix[l] = NULL;
    }
    return (matrix);
}

static void feed_matrix(t_item ***matrix, t_item *items, t_sd *sd, int directory)
{
    int     l;
    int     c;
    t_item  *start;
    
    l = 0;
    c = 0;
    start = NULL;
    if ((start = get_start(items)) && (items = start))
    {
        while (items)
        {
            if (l == sd->nb_lines)
            {
                l = 0;
                c++;
            }
            if (directory == 0 && items->child == NULL)
            {
                matrix[l][c] = items;
                l++;
            }
            else
            {
                matrix[l][c] = items;
                l++;
            }
            items = items->next;
        }
        while (l < sd->nb_lines)
        {
            matrix[l][c] = NULL;
            l++;
        }
        items = start;
    }
}

static void    free_matrix(t_item ***matrix)
{
    int i;
    
    i = 0;
    if (matrix)
    {
        while (matrix[i])
        {
            free(matrix[i]);
            i++;
        }
        free(matrix);
    }
}

static void display_matrix(t_item ***matrix, t_args *args)
{
    int l;
    int c;
    
    l = 0;
    c = 0;
    while (l < args->sd->nb_lines - 1)
    {
        if (c == args->sd->nb_col)
        {            
            c = 0;
            l++;
            ft_putchar('\n');
        }
        if (matrix[l][c])
        {
            display_name(matrix[l][c], args, 0);
            if (args->sd->nb_col > 1)
                display_blank_for_str(ft_strlen(matrix[l][c]->name),
                                args->sd->len_items, args->options->Q);
            c++;
        }
        else
            break ;
    }
    ft_putchar('\n');
}

static void no_need_matrix(t_item *items, t_args *args, int directory)
{
    t_item *start;
    int     i;
    
    i = 0;
    start = NULL;
    if (((start = get_start(items)) && ((items = start))))
    {
        while (items)
        {
            if (items->child == NULL)
            {
                i = 1;
                display_name(items, args, directory);
                ft_putstr("  ");
            }
            items = items->next;
        }
        if (i == 1)
            ft_putchar('\n');
        items = start;
        start = NULL;
    }
}

int        run_matrix(t_args *args, t_item *items, int directory)
{
    t_item  ***matrix;
    
    matrix = NULL;
    if (args->sd->nb_items == 0)
        return (0);
    set_matrix_size(args->sd, args->sd_ts);
    if (args->sd->nb_lines < 3)
        no_need_matrix(items, args, directory);
    else if (args->sd->nb_col == 1)
        return (1);
    else
    {
        matrix = create_matrix(args->sd);
        feed_matrix(matrix, items, args->sd, directory);
        display_matrix(matrix, args);
        free_matrix(matrix);
    }
    return (0);
}