/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 22:00:30 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 22:00:31 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_fdf.h"
#include "../libft/libft.h"

void	storepoint(t_stat *stat, char **r_p, t_view *view)
{
	int i;
	int x;
	int y;

	x = 0;
	y = 0;
	i = 0;
	while (y < stat->h)
	{
		while (x < stat->w)
		{
			view->map[y][x].x = (float)x;
			view->map[y][x].y = (float)y;
			view->map[y][x].z = (float)ft_atoi(r_p[i]);
			x++;
			i++;
		}
		y++;
		x = 0;
	}
}

void	read_points(char *str, int height, t_view *view, t_stat *stat)
{
	int l;
	int i;

	i = 0;
	l = stat->w;
	stat->h = height;
	view->map = (t_point**)malloc(sizeof(t_point*) * height);
	ft_bzero(view->map, sizeof(t_point*) * height);
	while (i < stat->h)
	{
		view->map[i] = (t_point*)malloc(sizeof(t_point) * l);
		ft_bzero(view->map[i], sizeof(t_point) * l);
		i++;
	}
	storepoint(stat, ft_strsplit(str, ' '), view);
}

int		counta(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*readfile(int fd, t_view *view, t_stat *stat)
{
	char	*ret;
	char	*line;
	int		count;

	count = 0;
	while (get_next_line(fd, &line))
	{
		if (count == 0)
		{
			ret = ft_strdup(line);
			stat->w = counta(ft_strsplit(ret, ' '));
		}
		else
		{
			ret = ft_strjoin(ret, " ");
			ret = ft_strjoin(ret, line);
		}
		if (counta(ft_strsplit(line, ' ')) != stat->w)
			tellerror();
		count++;
	}
	read_points(ret, count, view, stat);
	return (ret);
}
