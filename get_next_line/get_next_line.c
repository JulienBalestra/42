/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 17:59:06 by jubalest          #+#    #+#             */
/*   Updated: 2015/03/09 18:11:23 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int		treat_no_remain(char **line, char **remain, int fd, char *buf)
{
	if (ft_strchr(buf, '\n'))
	{
		if (**line)
			*line = ft_strjoin(ft_strdup(*line),
								ft_strndup(buf, ft_strchr(buf, '\n') - buf));
		else
			*line = ft_strndup(buf, ft_strchr(buf, '\n') - buf);
		remain[fd] = ft_strdup(ft_strchr(buf, '\n') + 1);
		return (*line && remain[fd] ? 1 : -1);
	}
	if (**line)
		*line = ft_strjoin(ft_strdup(*line), buf);
	else
		*line = ft_strdup(buf);
	return (*line && !remain ? 0 : -1);
}

static int		endl_in_remain(char **line, char **remain, int fd, char *buf)
{
	if (**line)
		*line = ft_strjoin(ft_strdup(*line), ft_strndup(remain[fd],
								ft_strchr(remain[fd], '\n') - remain[fd]));
	else
		*line = ft_strndup(remain[fd],
								ft_strchr(remain[fd], '\n') - remain[fd]);
	remain[fd] = ft_strjoin(ft_strdup(ft_strchr(remain[fd], '\n') + 1),
    											ft_strdup(buf));
	return (*line && remain[fd] ? 1 : -1);
}

static int		no_endl_in_remain(char **line, char *remain, char *buf, int ret)
{
	if (**line)
	{
		*line = ft_strjoin(ft_strdup(*line), remain);
		if (ret > 0)
			remain = ft_strdup(buf);
	}
	else
	{
		*line = ft_strdup(remain);
		if (ret > 0)
			remain = ft_strdup(buf);
	}
	if (ret < 1)
	{
		free(remain);
		remain = ft_strnew(0);
	}	
	return (**line && remain ? ret : -1);
}

static int		stream_to_line(int const fd, char *buf,
									char **line, char **remain)
{
	int			ret;

	ret = 0;
	if (!line || !remain[fd])
		return (-1);
	while (*remain[fd] != '\0' || ((int)ft_strlen(buf) < ret ? (0) :
			(ret = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if (*remain[fd] == '\0')
		{
			if (treat_no_remain(line, remain, fd, buf) == 1)
				return (1);
		}
		else if (ft_strchr(remain[fd], '\n'))
			return (endl_in_remain(line, remain, fd, buf));
		else
		{
			if (no_endl_in_remain(line, remain[fd], buf, ret) == -1)
				return (-1);
		}
	}
	if (ret > 0 || *remain[fd] != '\0' || **line != '\0')
		return (1);
	return (ret < 0 ? -1 : 0);
}

int				get_next_line(int const fd, char **line)
{
	static char	*remain[MAX_FD];
	int			stream_ret;
	char		buf[BUFF_SIZE];

	stream_ret = 0;
	if (fd < 0 || !line || BUFF_SIZE < 1 ||
			BUFF_SIZE > MAX_BUFF_SIZE)
		return (-1);
	*line = ft_strnew(0);
	if (!remain[fd])
		remain[fd] = ft_strnew(0);
	stream_ret = stream_to_line(fd, buf, line, remain);
	if (stream_ret > 0)
		return (1);
	if (*remain[fd])
		ft_strdel(&remain[fd]);
	ft_strdel(line);
	return (stream_ret);
}
