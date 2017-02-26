#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../libft/libft.h"
# include "./get_next_line.h"
# include <math.h>
# include <stdio.h>

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_stat
{
	float			h;
	float			w;
}					t_stat;

typedef struct		s_view
{
	void	*mlx;
	void	*window;
	void	*image;
	float		width;
	float		height;
	char 	*name;
	int		bpp;
	int		sl;
	int		edian;
	int		scalex;
	int		scaley;
	t_point	**map;
	t_stat	*stats;
}					t_view;

typedef	struct		s_rotation
{
	float	x;
	float	y;
	float	z;
	float	d;
	float	theta;
}					t_rotation;

float	get_m_z(t_view *view);
float	get_m_x(t_view *view);
float	get_m_y(t_view *view);
t_point	*centerfind(t_view *view);
#endif
