/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indent_date.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:52:20 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:53:34 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char	*pass_month_reduce(char *str_date)
{
	while (*str_date != ' ')
	{
		str_date++;
	}
	while (*str_date == ' ')
		str_date++;
	return (str_date);
}

static char	*len_day_number(t_ld *ld, char *str_date)
{
	int len;

	len = 0;
	while (*str_date != ' ')
	{
		len++;
		str_date++;
	}
	update_ld(&(ld->i_day), len, 0);
	return (str_date);
}

static void	len_hm_or_year(t_ld *ld, char *str_date)
{
	int		year;
	time_t	today_ts;

	year = convert_year(str_date);
	today_ts = time(&today_ts);
	if (((int)today_ts / 31556926) + 1970 == year)
		update_ld(&(ld->i_hm_year), 4, 0);
	else
		update_ld(&(ld->i_hm_year), 5, 0);
}

void		indent_date(t_ld *ld, time_t date)
{
	char	*str_date;

	str_date = ctime(&date);
	str_date = pass_weekday(str_date);
	str_date = pass_month_reduce(str_date);
	str_date = len_day_number(ld, str_date);
	len_hm_or_year(ld, str_date);
}
