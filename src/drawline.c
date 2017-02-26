/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 21:00:02 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 21:00:03 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/FdF.h"
#include "../libft/libft.h"

int		swap_var(t_point p0, t_point p1)
{
	float temp;

	if (fabs(p1.x - p0.x) > fabs(p1.y - p0.y))
		return (0);
	temp = p0.y;
	p0.y = p0.x;
	p0.x = temp;
	temp = p1.y;
	p1.y = p1.x;
	p1.x = temp;
	return (1);
}

void	drawline(t_view *view, t_point p0, t_point p1)
{
	float	delta[3];
	float	error;
	float	slope;
	int		dir;

	dir = swap_var(p0, p1);
	delta[0] = p1.x - p0.x;
	delta[1] = p1.y - p0.y;
	delta[2] = p1.z - p0.z;
	slope = fabs(delta[1] / delta[0]);
	error = -1.0;
	while ((int)p0.x != (int)p1.x)
	{
		mlx_pixel_put(view->mlx,
		view->window, dir ? p0.y : p0.x, dir ? p0.x : p0.y, 0x00FF00);
		error += slope;
		if (error >= 0.0)
		{
			p0.y += (p0.y > p1.y) ? -1.0 : 1.0;
			error -= 1.0;
		}
		p0.x += (p0.x > p1.x) ? -1.0 : 1.0;
	}
}

void	drawline_y(t_view *view, t_point p0, t_point p1)
{
	float	delta[3];
	float	error;
	float	slope;
	int		dir;

	dir = swap_var(p0, p1);
	delta[0] = p1.y - p0.y;
	delta[1] = p1.x - p0.x;
	delta[2] = p1.z - p0.z;
	slope = fabs(delta[1] / delta[0]);
	error = -1.0;
	while ((int)p0.y != (int)p1.y)
	{
		mlx_pixel_put(view->mlx,
		view->window, dir ? p0.x : p0.y, dir ? p0.y : p0.x, 0x00FF00);
		error += slope;
		if (error >= 0.0)
		{
			p0.x += (p0.x > p1.x) ? -1.0 : 1.0;
			error -= 1.0;
		}
		p0.y += (p0.y > p1.y) ? -1.0 : 1.0;
	}
}

void	draw_w(float delta, t_view *view, int x, int y)
{
	if (delta < 1.0f)
		drawline_y(view, view->map[y][x], view->map[y][x + 1]);
	else
		drawline(view, view->map[y][x], view->map[y][x + 1]);
}

void	draw_h(float delta, t_view *view, int x, int y)
{
	if (delta >= 1.0f)
		drawline_y(view, view->map[y][x], view->map[y + 1][x]);
	else
		drawline_y(view, view->map[y][x], view->map[y + 1][x]);
}
