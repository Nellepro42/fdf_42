/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 16:41:03 by neprocur          #+#    #+#             */
/*   Updated: 2015/10/31 22:18:57 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define M_PI 3.14159265358979323846

# include "libft.h"
# include "fdf.h"
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define WIDTH	2000
# define HEIGHT	1000
# define CTE1	0.75
# define CTE2	0.75
# define MORE	69
# define LESS	78
# define ESC		53
# define LEFT	123
# define RIGHT	124
# define H		126
# define B		125
# define ENDIAN	&e->endian
# define SIZEL	&e->sizeline
# define END 	e->end

typedef	struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_env
{
	int			p;
	int			n;
	int			i;
	int			end;
	int			move_up;
	int			move_down;
	int			move_right;
	int			move_left;
	int			dflt;
	int			height;
	int			width;
	void		*mlx;
	void		*win;
	int			line;
	int			column;
	t_point		**tabl;
	t_point		**tabl1;
	t_point		**tabl2;
	t_point		center;
	int			zoom;
	int			size;
	int			dx;
	int			dy;
	int			err;
	int			sx;
	int			sy;
	int			e2;
	int			bpp;
	int			sizeline;
	int			endian;
	char		*img_ptr;
	void		*img_str;
	int			x_move;
	int			y_move;
	int			z_move;
}				t_env;

t_point			**ft_alloc_struct(t_env *e);
void			draw_map(t_env *e);
void			assign_iso(t_env *e);
int				key_hook(int keycode, t_env *e);
int				ft_loop_hook(t_env *e);
int				ft_key_hook(int keycode, t_env *e);
void			ft_key_esc(t_env *e);
void			ft_init_window(t_env *e);

#endif
