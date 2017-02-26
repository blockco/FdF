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

int		checkkey(int key, t_view *view)
{
	if (key == 53)
	{
		free(view);
		exit(1);
	}
	return (1);
}

int		checkex(t_view *view)
{
	addpixels(view, view->stats);
	return (0);
}

void	initview(t_view *view, t_stat *stat)
{
	view->stats = stat;
	view->mlx = mlx_init();
	view->width = 1600;
	view->height = 800;
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
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		readfile(fd, view, stat);
	}
	else
		tellerror();
	initview(view, stat);
	view->window = mlx_new_window(view->mlx, view->width, view->height, "FdF");
	scalepoints(view, stat);
	pads(view);
	xrotation(view, -.2);
	addpixels(view, stat);
	mlx_key_hook(view->window, checkkey, view);
	mlx_expose_hook(view->window, checkex, view);
	mlx_loop(view->mlx);
}
