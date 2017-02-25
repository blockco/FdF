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
	int			h;
	int			w;
}					t_stat;

typedef struct		s_view
{
	void	*mlx;
	void	*window;
	void	*image;
	int		width;
	int		height;
	char 	*name;
	int		bpp;
	int		sl;
	int		edian;
	int		scalex;
	int		scaley;
	t_point	**map;
	t_stat	*stats;
}					t_view;
#endif
