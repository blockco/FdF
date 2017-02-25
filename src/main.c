#include "../headers/FdF.h"
#include "../libft/libft.h"
#include <stdio.h>

// int findlen(char *map, int h)
// {
// 	int i;
// 	int ret;
//
// 	ret = 0;
// 	i = 0;
// 	while (*map)
// 	{
// 		if ()
// 	}
// 	return(ret);
// }

void storepoint(int l, char** r_p, t_point **map)
{
	int i;
	int count;
	int x;
	int y;

	x = 0;
	y = 0;
	i = 0;
	while (r_p[i])
	{
		map[y][x].x = (float)x;
		map[y][x].y = (float)y;
		map[y][x].z = (float)ft_atoi(r_p[i]);
		// printf("%f\n%f\n%f\n\n", map[y][x].x, map[y][x].y, map[y][x].z);
		x++;
		if (x == l)
		{
			y++;
			x = 0;
		}
		i++;
	}
}

void read_points(char *str, int height, t_point **map, t_stat *stat)
{
	int l;
	int i;

	i = 0;
	l = stat->w;
	stat->h = height;
	printf("%d\n%d\n", stat->h, stat->w);
	map = (t_point**)malloc(sizeof(t_point*) * height);
	while (i < l)
	{
		map[i] = (t_point*)malloc(sizeof(t_point) * l);
		i++;
	}
	//ft_putendl("here");
	storepoint(l, ft_strsplit(str,' '), map);
}

//validate map

int counta(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char *readfile(int fd, t_point **map, t_stat *stat)
{
	char *ret;
	char *line;
	int count;
	int len;

	count  = 0;
	while (get_next_line(fd, &line))
	{
		if (count == 0)
		{
			ret = ft_strdup(line);
			len = counta(ft_strsplit(ret, ' '));
			stat->w = len;
		}
		else
			ret = ft_strjoin(ret, line);
		if (counta(ft_strsplit(line, ' ')) != len)
		{
			ft_putendl("error");
			exit(0);
		}
		count++;
	}
	read_points(ret, count, map, stat);
	return (ret);
}

void addpixels(t_view *view, t_stat *stat)
{
	int	x;
	int	y;
	int	px;
	int	py;

	x = 0;
	y = 0;
	px = view->width / stat->w;
	py = view->height / stat->h;
	while(y < stat->h)
	{
		mlx_pixel_put(view->mlx, view->window, px, py, 0x00FF00);
		// ft_putendl("here");
		// printf("%f\n%f\n%f\n", view->map[y][x].x, view->map[y][x].y, view->map[y][x].z);
		px += view->width / stat->w;
		if (x == stat->w)
		{
			y++;
			x = 0;
			px = view->width / stat->w;
			py += view->height / stat->h;
		}
		x++;
	}
}

int main(int argc, char *argv[])
{
	int fd;
	t_view	*view;
	t_stat	*stat;

	stat = (t_stat*)malloc(sizeof(t_stat));
	view = (t_view*)malloc(sizeof(t_view));
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		readfile(fd, view->map, stat);
	}
	view->mlx = mlx_init();
	view->width = 1000;
	view->height = 1000;
	view->window = mlx_new_window(view->mlx, view->width, view->height, "FdF");
	addpixels(view, stat);
	mlx_loop(view->mlx);
	//	return 0;
}
