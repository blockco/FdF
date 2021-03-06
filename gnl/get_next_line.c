/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 22:04:22 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 22:04:25 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_tmp(const int fd, char **buff)
{
	char	tmp[BUFF_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(*buff, '\n') == NULL)
	{
		bytes_read = read(fd, &tmp, BUFF_SIZE);
		if (bytes_read < 0)
			return (-1);
		tmp[bytes_read] = '\0';
		*buff = ft_strjoin(*buff, (const char*)tmp);
		ft_bzero(tmp, BUFF_SIZE);
	}
	return (bytes_read);
}

int		get_line(char **buff, char **line)
{
	char *str;

	str = ft_strchr(*buff, '\n');
	if (str)
	{
		str[0] = '\0';
		*line = ft_strdup(*buff);
		*buff = str + 1;
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char *buff;
	int			bytes_read;

	if (fd < 0 || line == NULL || (-1 == read(fd, buff, 0)))
		return (-1);
	if (!buff)
		buff = ft_strnew(BUFF_SIZE);
	bytes_read = read_tmp(fd, &buff);
	if (bytes_read == -1)
		return (-1);
	if (get_line(&buff, line))
		return (1);
	*line = ft_strdup(buff);
	buff = NULL;
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
