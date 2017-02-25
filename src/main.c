#include "../headers/FdF.h"
#include "../libft/libft.h"
#include <stdio.h>

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
			// printf("%d\n%d\n%s\n%d\n\n", x, y, r_p[i], i);
			x++;
			i++;
		}
		y++;
		x = 0;
	}
}

void read_points(char *str, int height, t_view *view, t_stat *stat)
{
	int l;
	int i;

	i = 0;
	l = stat->w;
	stat->h = height;
	// printf("%d\n%d\n", stat->h, stat->w);
	view->map = (t_point**)malloc(sizeof(t_point*) * height);
	while (i < l)
	{
		view->map[i] = (t_point*)malloc(sizeof(t_point) * l);
		i++;
	}
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

void drawline_y(t_view *view, t_point p0, t_point p1)
{
	float delta[3];
	float error;
	float slope;
	int dir;

	dir = swap_var(p0,p1);
	delta[0] = p1.y - p0.y;
	delta[1] = p1.x - p0.x;
	delta[2] = p1.z - p0.z;
	slope = fabs(delta[1] / delta[0]);
	error = -1.0;
	while ((int)p0.y != (int)p1.y)
	{
		mlx_pixel_put(view->mlx, view->window, dir ? p0.x : p0.y, dir ? p0.y : p0.x, 0x00FF00);
		error += slope;
		if (error >= 0.0)
		{
			p0.x += (p0.x > p1.x) ? -1.0 : 1.0;
			error -= 1.0;
		}
		p0.y += (p0.y > p1.y) ? -1.0 : 1.0;
	}
}

void scalepoints(t_view *view, t_stat *stat)
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
			view->map[y][x].x = view->map[y][x].x * ((view->width / stat->w) / 2);
			view->map[y][x].y = view->map[y][x].y * ((view->width / stat->w) / 2);
			view->map[y][x].z = view->map[y][x].z * ((view->width / stat->w) / 2);
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
	float d_x;
	float d_y;
	float delta;

	x = 0;
	y = 0;
	scalepoints(view, stat);
	while(y < stat->h)
	{
		d_x = fabs(view->map[y][x + 1].x - view->map[y][x].x);
		d_y = fabs(view->map[y][x + 1].y - view->map[y][x].y);
		delta = d_x / d_y;
		mlx_pixel_put(view->mlx, view->window, view->map[y][x].x, view->map[y][x].y, 0x00FF00);
		if (x < stat->w - 1)
		{
			if (delta < 1.0f)
				drawline_y(view, view->map[y][x], view->map[y][x + 1]);
			else
				drawline(view, view->map[y][x], view->map[y][x + 1]);
		}
		if (y < stat->h - 1.0f)
			{
				if (delta >= 1.0f)
					drawline_y(view, view->map[y][x], view->map[y + 1][x]);
				else
					drawline(view, view->map[y][x], view->map[y + 1][x]);
			}
		if (x == stat->w)
		{
			y++;
			x = 0;
		}
		else
			x++;
	}
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
	while(y < view->stats->h)
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
	ft_putendl("here");
	while(y < view->stats->h)
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
	while(y < view->stats->h)
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

t_point	*centerfind(t_view *view)
{
	t_point *ret;

	ret = (t_point*)malloc(sizeof(t_point));

	ret->x = get_m_x(view);
	ret->y = get_m_y(view);
	ret->z = get_m_z(view);
	return (ret);
}

void xrotation(t_view *view, float rad)
{
	int x;
	int y;
	t_rotation 	r_points;
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
	view->stats = stat;
	view->mlx = mlx_init();
	view->width = 800;
	view->height = 600;
	view->window = mlx_new_window(view->mlx, view->width, view->height, "FdF");
	xrotation(view, -.2);
	addpixels(view, stat);
	mlx_loop(view->mlx);
}
