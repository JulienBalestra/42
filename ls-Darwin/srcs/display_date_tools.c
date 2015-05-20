/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_date_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 11:12:44 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 11:13:04 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*pass_weekday(char *str_date)
{
	while (*str_date++ != ' ')
		;
	while (*str_date == ' ')
		str_date++;
	return (str_date);
}

int		convert_year(char *str_date)
{
	str_date = display_hm_or_pass_hms(str_date, 0);
	return (ft_atoi(str_date));
}
