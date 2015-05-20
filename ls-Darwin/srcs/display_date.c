/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_date.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 18:14:01 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/12 18:16:32 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char	*display_month_reduce(char *str_date)
{
	while (*str_date != ' ')
	{
		ft_putchar(*str_date);
		str_date++;
	}
	ft_putchar(*str_date);
	while (*str_date == ' ')
		str_date++;
	return (str_date);
}

static char	*display_day_number(char *str_date, int i_day)
{
	int	len;

	len = 0;
	while (str_date[len] != ' ')
		len++;
	while (len < i_day)
	{
		ft_putchar(' ');
		len++;
	}
	while (*str_date != ' ')
	{
		ft_putchar(*str_date);
		str_date++;
	}
	ft_putchar(*str_date);
	while (*str_date == ' ')
		str_date++;
	return (str_date);
}

char		*display_hm_or_pass_hms(char *str_date, int display)
{
	int sep;

	sep = 0;
	while (*str_date != ' ')
	{
		if (*str_date == ':')
			sep++;
		if (display && (sep == 0 || sep == 1))
			ft_putchar(*str_date);
		str_date++;
	}
	if (display)
		ft_putchar(*str_date++);
	else
	{
		while (*str_date == ' ')
			str_date++;
	}
	return (str_date);
}

void		display_hm_or_year(char *str_date, time_t file_date, int i_hm_year)
{
	int		year;
	time_t	today_ts;

	year = convert_year(str_date);
	today_ts = time(&today_ts);
	if (((today_ts / 31556926) + 1970 == year) || (
		((file_date + 15770000) >= today_ts) &&
		((file_date - 15770000) <= today_ts)))
		display_hm_or_pass_hms(str_date, 1);
	else
	{
		str_date = display_hm_or_pass_hms(str_date, 0);
		if (i_hm_year == 5)
			ft_putchar(' ');
		ft_putnbr(year);
		ft_putchar(' ');
	}
}

void		display_date(time_t date, t_ld *ld)
{
	char *str_date;

	str_date = ctime(&date);
	str_date = pass_weekday(str_date);
	str_date = display_month_reduce(str_date);
	str_date = display_day_number(str_date, ld->i_day);
	display_hm_or_year(str_date, date, ld->i_hm_year);
}
