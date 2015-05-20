/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:09:43 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:50:43 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include "libft.h"
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

typedef struct	s_opt
{
	int			one;
	int			l;
	int			re;
	int			a;
	int			r;
	int			t;
	int			si;
	int			gr;
	int			g;
	int			d;
	int			q;
	int			u;
	int			f;
	int			color;
	int			c;
}				t_opt;

typedef struct	s_i
{
	char		*name;
	char		*path;
	struct s_i	*next;
	struct s_i	*prev;
	struct s_i	*child;
	struct s_i	*parent;
	struct stat	*stats;
}				t_item;

typedef struct	s_ld
{
	int			i_nlink;
	int			i_gid;
	int			i_uid;
	int			i_size;
	int			i_month;
	int			i_day;
	int			i_hm_year;
	int			total_blocks;
	int			i_major;
	int			i_minor;
}				t_ld;

typedef struct	s_sd_props
{
	int			len_items;
	int			nb_items;
	int			nb_col;
	int			nb_lines;
}				t_sd;

typedef struct	s_args
{
	t_opt		*options;
	t_item		*items;
	int			ret;
	int			inputs;
	t_ld		*ld;
	t_sd		*sd;
	int			sd_ts;
	int			(*compare)(t_item *one, t_item *two, int reverse);
}				t_args;

typedef struct	s_sort
{
	t_item		*right;
	t_item		*temp;
	t_item		*last;
	t_item		*result;
	t_item		*next;
	t_item		*tail;
}				t_sort;

int				how_many_option(t_opt *option);
t_args			*ft_get_args(int ac, char **av);
void			ft_get_items(t_args *args, char *av, int from_av);
void			ft_get_options(t_args *args, char *av);
t_item			*new_link(char const *name, t_item *parent, t_args *args);
void			add_link(t_item **alist, t_item *new_link, int end);
void			remove_link(t_item *link);
void			refresh_index(t_item *link);
t_item			*get_start(t_item *link);
t_item			*get_end(t_item *link);
void			del_list(t_item **alist, int way);
void			destroy_link(t_item *link);
void			clean_items(t_item *item);
void			clean_program(t_args **args);
void			create_children(t_item *parents, t_args *args);
DIR				*open_dir(char *file_name);
t_item			*merge_sort_list_recursive(t_item *list, t_args *args);
void			set_merge(t_sort *merge, t_item *list);
void			long_display(t_item *items, t_args *args);
void			short_display(t_item *items, t_args *args);
void			display_protection(mode_t st_mode, char *path);
void			display_hard_link(nlink_t st_nlink, int i_nlink);
void			display_id(struct stat *stats, t_args *args);
void			display_dev_or_size(struct stat *stats, t_ld *ld);
void			display_date(time_t date, t_ld *ld);
void			cannot_open(t_item *link, t_args *args);
void			cannot_access(t_item *link, t_args *args);
void			invalid_option(t_args *args, char *av);
char			*display_hm_or_pass_hms(char *str_date, int display);
char			*pass_weekday(char *str_date);
int				convert_year(char *str_date);
t_ld			*create_ld(void);
void			update_ld(int *indent, int stat_obj, int calculate_int_len);
void			*get_ld(struct stat *stats, t_ld *ld);
void			set_ld(t_ld *ld);
void			display_total_blocks(int total_blocks);
void			display_blank_for_digits(int use_case, int indent);
void			indent_date(t_ld *ld, time_t date);
char			get_illegal(char *av);
void			not_enough_memory(t_args *args);
void			verbose_invalid_option(char *av);
void			verbose_not_enough_memory(void);
void			display_symbolic_link(t_item *items, t_args *args);
int				is_symbolic_link(t_item *link);
int				is_directory(t_item *link);
void			deep_in_directories(t_item *child_to_parent, t_args *args);
void			iter_on_links(t_item *items, t_ld *ld, int file_only);
void			selected_print(t_item *items, t_args *args);
void			recurse_in_directory(t_item *child_to_parent, t_args *args);
void			choose_pivot(t_args *args);
void			display_name(t_item *items, t_args *args, int directory);
int				get_columns(void);
void			iter_for_len(t_item *items, t_args *args, int directory);
t_sd			*create_sd_props(void);
int				run_matrix(t_args *args, t_item *items, int directory);
void			display_blank_for_str(int strlen, int indent, int q);
int				round_up(int a, int b);
int				min(int a, int b);
int				browse_arguments_for_items(t_args *args, int opt,
										int ac, char **av);
void			recurse_browse_arguments_for_items(t_args *args, int opt,
										int ac, char **av);
int				file_display(t_item *items, t_args *args);
int				display_file_only(t_item *items, t_args *args);
void			set_color(mode_t mode);
int				uidlen(int uid, int pw);
void			putuid(int uid, int pw);
int				is_other_dir(t_item *items);
void			replay_directory(t_item *items, t_args *args);
void			display_endline(t_item *items);
void			get_sorted_av(char **av, int opt, int ac);
void			find_options(t_opt *options, char *av);
void			set_matrix_size(t_sd *sd, int sd_ts);
void			free_matrix(t_item ***matrix);
void			iter_file_display(t_item *items, t_args *args, int ret);
int				try_rights(char *path);
void			no_directory_display(t_item *items, t_args *args);

#endif
