/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 21:11:34 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 21:11:35 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_fdf.h"
#include "../libft/libft.h"

void		scalepoints(t_view *view, t_stat *stat)
{
	int x;
	int y;
	int mx;
	int my;

	mx = get_m_x(view);
	my = get_m_y(view);
	x = 0;
	y = 0;
	while (y < stat->h)
	{
		while (x < stat->w)
		{
			view->map[y][x].x *= ((view->height / stat->h) / 2);
			view->map[y][x].y *= ((view->height / stat->h) / 2);
			view->map[y][x].z *= ((view->width / stat->w) / 2);
			x++;
		}
		x = 0;
		y++;
	}
}

t_point		*centerfind(t_view *view)
{
	t_point *ret;

	ret = (t_point*)malloc(sizeof(t_point));
	ft_bzero(ret, sizeof(t_point));
	ret->x = get_m_x(view);
	ret->y = get_m_y(view);
	ret->z = get_m_z(view);
	return (ret);
}

void		xrotation(t_view *view, float rad)
{
	int			x;
	int			y;
	t_rotation	r_points;
	t_point		*middle;

	middle = centerfind(view);
	y = 0;
	while (y < view->stats->h)
	{
		x = 0;
		while (x < view->stats->w)
		{
			r_points.y = view->map[y][x].y - middle->y;
			r_points.z = view->map[y][x].z - middle->z;
			r_points.d = hypot(r_points.y, r_points.z);
			r_points.theta = atan2(r_points.y, r_points.z) + rad;
			view->map[y][x].z = r_points.d * cos(r_points.theta) + middle->z;
			view->map[y][x].y = r_points.d * sin(r_points.theta) + middle->y;
			x++;
		}
		y++;
	}
}

void		pads(t_view *view)
{
	int x;
	int y;

	y = 0;
	while (y < view->stats->h)
	{
		x = 0;
		while (x < view->stats->w)
		{
			view->map[y][x].x += (view->width) / 4;
			view->map[y][x].y += (view->height) / 4;
			x++;
		}
		y++;
	}
}
