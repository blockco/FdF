/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 22:02:28 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 22:02:29 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_fdf.h"
#include "../libft/libft.h"

void	tellerror(void)
{
	ft_putendl("error");
	exit(0);
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

int		checkkey(int key, t_view *view)
{
	if (key == 53)
	{
		free(view);
		exit(1);
	}
	return (1);
}

int		main(int argc, char *argv[])
{
	int		fd;
	t_view	*view;
	t_stat	*stat;

	stat = (t_stat*)malloc(sizeof(t_stat));
	view = (t_view*)malloc(sizeof(t_view));
	ft_bzero(view, sizeof(t_view));
	ft_bzero(stat, sizeof(t_stat));
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		readfile(fd, view, stat);
	}
	view->stats = stat;
	view->mlx = mlx_init();
	view->width = 1600;
	view->height = 800;
	view->window = mlx_new_window(view->mlx, view->width, view->height, "FdF");
	scalepoints(view, stat);
	pads(view);
	xrotation(view, -.2);
	addpixels(view, stat);
	mlx_key_hook(view->window, checkkey, view);
	mlx_loop(view->mlx);
}
