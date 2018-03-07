/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 18:13:18 by neprocur          #+#    #+#             */
/*   Updated: 2015/10/31 17:36:21 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_pixel_put(t_env *e, int x, int y, int color)
{
	int		res;

	res = x * e->bpp / 8 + y * e->sizeline;
	if ((x < WIDTH) && (y < HEIGHT) && (x > 0) && (y > 0) && (res > 0))
	{
		if (e->endian)
		{
			e->img_ptr[res] = color;
			e->img_ptr[res + 1] = color >> 8;
			e->img_ptr[res + 2] = color >> 16;
		}
		else
		{
			e->img_ptr[res] = color >> 16;
			e->img_ptr[res + 1] = color >> 8;
			e->img_ptr[res + 2] = color;
		}
	}
}

void		draw_line(t_point p0, t_point p1, t_env *e)
{
	e->dx = abs(p1.x - p0.x);
	e->sx = p0.x < p1.x ? 1 : -1;
	e->dy = abs(p1.y - p0.y);
	e->sy = p0.y < p1.y ? 1 : -1;
	e->err = (e->dx > e->dy ? e->dx : -e->dy) / 2;
	while (42)
	{
		ft_pixel_put(e, p0.x, p0.y, 0x0000FF);
		e->e2 = e->err;
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		if (e->e2 > -e->dx)
		{
			e->err -= e->dy;
			p0.x += e->sx;
		}
		if (e->e2 < e->dy)
		{
			e->err += e->dx;
			p0.y += e->sy;
		}
	}
}

void		assign_iso(t_env *e)
{
	t_point	t;

	t.x = 0;
	t.y = 0;
	t.z = 0;
	e->p = 0;
	e->n = 0;
	e->tabl2 = ft_alloc_struct(e);
	while (e->p < e->line)
	{
		while (e->n < e->column)
		{
			t.z = e->tabl[e->p][e->n].z * e->z_move;
			t.x = e->tabl[e->p][e->n].x * e->zoom;
			t.y = e->tabl[e->p][e->n].y * e->zoom;
			e->tabl2[e->p][e->n].x = CTE1 * t.x - CTE2 * t.y + WIDTH / 3 +
			e->x_move;
			e->tabl2[e->p][e->n].y = (CTE1 / 2) * t.x + (CTE2 / 2) * t.y - t.z +
			HEIGHT / 6 + e->y_move;
			e->n++;
		}
		e->n = 0;
		e->p++;
	}
}

void		draw_map2(t_env *e)
{
	while (e->p < e->line - 1)
	{
		while (e->n < e->column)
		{
			draw_line(e->tabl2[e->p][e->n], e->tabl2[e->p + 1][e->n], e);
			e->n++;
		}
		e->n = 0;
		e->p++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_str, 0, 0);
}

void		draw_map(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img_str);
	e->img_str = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	assign_iso(e);
	e->p = 0;
	e->n = 0;
	while (e->p < e->line)
	{
		while (e->n < e->column - 1)
		{
			draw_line(e->tabl2[e->p][e->n], e->tabl2[e->p][e->n + 1], e);
			e->n++;
		}
		e->n = 0;
		e->p++;
	}
	e->p = 0;
	e->n = 0;
	draw_map2(e);
}
