/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display_props.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 12:01:51 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 12:02:38 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_ld	*create_ld(void)
{
	t_ld	*ld;

	ld = NULL;
	if ((ld = (t_ld *)malloc(sizeof(t_ld))))
		set_ld(ld);
	return (ld);
}

void	set_ld(t_ld *ld)
{
	ld->i_nlink = 0;
	ld->i_gid = 0;
	ld->i_uid = 0;
	ld->i_size = 0;
	ld->i_month = 0;
	ld->i_day = 2;
	ld->i_hm_year = 0;
	ld->total_blocks = 0;
	ld->i_major = 0;
	ld->i_minor = 0;
}

void	update_ld(int *indent, int stat_obj, int calculate_int_len)
{
	if (calculate_int_len == 1)
		stat_obj = ft_nbrlen(stat_obj);
	if (stat_obj > *indent)
		*indent = stat_obj;
}

void	*get_ld(struct stat *stats, t_ld *ld)
{
	if (stats && ld)
	{
		update_ld(&(ld->i_nlink), (int)(stats->st_nlink), 1);
		update_ld(&(ld->i_uid), uidlen(stats->st_uid, 1), 0);
		update_ld(&(ld->i_gid), uidlen(stats->st_gid, 1), 0);
		update_ld(&(ld->i_gid), uidlen(stats->st_gid, 0), 0);
		if (S_ISBLK(stats->st_mode) || S_ISCHR(stats->st_mode))
		{
			update_ld(&(ld->i_major), (int)major(stats->st_rdev), 1);
			update_ld(&(ld->i_size), (int)minor(stats->st_rdev) * 10, 1);
		}
		else
			update_ld(&(ld->i_size), (int)(stats->st_size), 1);
		ld->total_blocks = ld->total_blocks + (int)((stats->st_blocks));
		indent_date(ld, stats->st_mtime);
	}
	return (ld);
}
