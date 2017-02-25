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

void storepoint(t_stat *stat, char** r_p, t_view *view)
{
	int i;
	int count;
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
			printf("%d\n%d\n%s\n%d\n\n", x, y, r_p[i], i);
			x++;
			i++;
		}
		y++;
		x = 0;
		// if (x == l - 1)
		// {
		// 	y++;
		// 	x = 0;
		// }
		// x++;
	}
}

void read_points(char *str, int height, t_view *view, t_stat *stat)
{
	int l;
	int i;

	i = 0;
	l = stat->w;
	stat->h = height;
	printf("%d\n%d\n", stat->h, stat->w);
	view->map = (t_point**)malloc(sizeof(t_point*) * height);
	while (i < l)
	{
		view->map[i] = (t_point*)malloc(sizeof(t_point) * l);
		i++;
	}
	//ft_putendl("here");
	storepoint(stat, ft_strsplit(str,' '), view);
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

char *readfile(int fd, t_view *view, t_stat *stat)
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
		{
			ret = ft_strjoin(ret, " ");
			ret = ft_strjoin(ret, line);
		}
		if (counta(ft_strsplit(line, ' ')) != len)
		{
			ft_putendl("error");
			exit(0);
		}
		count++;
	}
	read_points(ret, count, view, stat);
	return (ret);
}

int swap_var(t_point p0, t_point p1)
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
	return 1;
}

void drawline(t_view *view, t_point p0, t_point p1)
{
	float delta[3];
	float error;
	float slope;
	int dir;

	dir = swap_var(p0,p1);
	delta[0] = p1.x - p0.x;
	delta[1] = p1.y - p0.y;
	delta[2] = p1.z - p0.z;
	slope = fabs(delta[1] / delta[0]);
	error = -1.0;
	while ((int)p0.x != (int)p1.x)
	{
		mlx_pixel_put(view->mlx, view->window, dir ? p0.y : p0.x, dir ? p0.x : p0.y, 0x00FF00);
		error += slope;
		if (error >= 0.0)
		{
			p0.y += (p0.y > p1.y) ? -1.0 : 1.0;
			error -= 1.0;
		}
		p0.x += (p0.x > p1.x) ? -1.0 : 1.0;
	}
}

void scalepoints(t_view *view, t_stat *stat)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < stat->h)
	{
		while (x < stat->w)
		{
			// printf("before: %f\n%f\n\n", view->map[y][x].x, view->map[y][x].y);
			view->map[y][x].x = view->map[y][x].x * (view->width / stat->w);
			view->map[y][x].y = view->map[y][x].y * (view->height / stat->h);
			// printf("after: %f\n%f\n\n", view->map[y][x].x, view->map[y][x].y);
			x++;
		}
		x = 0;
		y++;
	}
}

void addpixels(t_view *view, t_stat *stat)
{
	int	x;
	int	y;
	int	px;
	int	py;

	x = 0;
	y = 0;
	// px = 0;
	// py = 0;
	scalepoints(view, stat);
	while(y < stat->h)
	{
		mlx_pixel_put(view->mlx, view->window, view->map[y][x].x+1, view->map[y][x].y+1, 0x00FF00);
		// if (x < stat->w - 1)
		// 	drawline(view, view->map[y][x], view->map[y][x + 1]);
		// else if (y < stat->h - 1)
		// 	drawline(view, view->map[y][x], view->map[y + 1][x]);
		if (x == stat->w)
		{
			y++;
			x = 0;
			// px = 0;
			// py += view->height / stat->h;
		}
		else
		{
			// px += view->width / stat->w;
			x++;
		}
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
		readfile(fd, view, stat);
	}
	view->mlx = mlx_init();
	view->width = 700;
	view->height = 700;
	view->window = mlx_new_window(view->mlx, view->width, view->height, "FdF");
	addpixels(view, stat);
	mlx_loop(view->mlx);
	//	return 0;
}
