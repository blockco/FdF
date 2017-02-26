#include "../headers/FdF.h"
#include "../libft/libft.h"

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
