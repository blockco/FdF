/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 22:03:21 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 22:03:22 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_fdf.h"
#include "../libft/libft.h"

void	checkfd(int fd)
{
	if (fd == -1)
		tellerror();
}

float	get_m_y(t_view *view)
{
	int		i;
	int		y;
	int		x;
	float	sum;

	i = 0;
	y = 0;
	sum = 0;
	while (y < view->stats->h)
	{
		x = 0;
		while (x < view->stats->w)
		{
			sum += view->map[y][x].y;
			i++;
			x++;
		}
		y++;
	}
	return (sum / (float)i);
}

float	get_m_x(t_view *view)
{
	int		i;
	int		y;
	int		x;
	float	sum;

	i = 0;
	y = 0;
	sum = 0;
	while (y < view->stats->h)
	{
		x = 0;
		while (x < view->stats->w)
		{
			sum += view->map[y][x].x;
			i++;
			x++;
		}
		y++;
	}
	return (sum / (float)i);
}

float	get_m_z(t_view *view)
{
	int		i;
	int		y;
	int		x;
	float	sum;

	i = 0;
	y = 0;
	sum = 0;
	while (y < view->stats->h)
	{
		x = 0;
		while (x < view->stats->w)
		{
			sum += view->map[y][x].z;
			i++;
			x++;
		}
		y++;
	}
	return (sum / (float)i);
}

void	addpixels(t_view *view, t_stat *stat)
{
	int		x;
	int		y;
	float	delta;

	x = 0;
	y = 0;
	while (y < stat->h)
	{
		delta = fabs(view->map[y][x + 1].x - view->map[y][x].x) /
		fabs(view->map[y][x + 1].y - view->map[y][x].y);
		if (x < stat->w - 1)
			draw_w(delta, view, x, y);
		if (y < stat->h - 1)
			draw_h(delta, view, x, y);
		if (x == stat->w - 1)
		{
			y++;
			x = 0;
		}
		else
			x++;
	}
}
