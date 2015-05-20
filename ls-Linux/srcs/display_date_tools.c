#include "ls.h"

char	*pass_weekday(char *str_date)
{
	while (*str_date++ != ' ')
		;
	while (*str_date == ' ')
		str_date++;
	return (str_date);
}

int	convert_year(char *str_date)
{
	str_date = display_hm_or_pass_hms(str_date, 0);
	return (ft_atoi(str_date));
}