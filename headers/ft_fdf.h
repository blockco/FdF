/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 22:10:09 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/25 22:10:10 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

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
	void			*mlx;
	void			*window;
	void			*image;
	float			width;
	float			height;
	char			*name;
	int				bpp;
	int				sl;
	int				edian;
	int				scalex;
	int				scaley;
	t_point			**map;
	t_stat			*stats;
}					t_view;

typedef	struct		s_rotation
{
	float			x;
	float			y;
	float			z;
	float			d;
	float			theta;
}					t_rotation;

float				get_m_z(t_view *view);
float				get_m_x(t_view *view);
float				get_m_y(t_view *view);
t_point				*centerfind(t_view *view);
void				storepoint(t_stat *stat, char **r_p, t_view *view);
void				read_points(char *str, int height, t_view
					*view, t_stat *stat);
int					counta(char **str);
void				tellerror();
char				*readfile(int fd, t_view *view, t_stat *stat);
int					swap_var(t_point p0, t_point p1);
void				drawline(t_view *view, t_point p0, t_point p1);
void				drawline_y(t_view *view, t_point p0, t_point p1);
void				scalepoints(t_view *view, t_stat *stat);
void				draw_w(float delta, t_view *view, int x, int y);
void				draw_h(float delta, t_view *view, int x, int y);
void				addpixels(t_view *view, t_stat *stat);
float				get_m_y(t_view *view);
float				get_m_x(t_view *view);
float				get_m_z(t_view *view);
t_point				*centerfind(t_view *view);
void				xrotation(t_view *view, float rad);
void				pads(t_view *view);
int					checkkey(int key, t_view *view);
void				checkfd(int fd);
#endif
