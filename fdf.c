/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 10:10:16 by neprocur          #+#    #+#             */
/*   Updated: 2015/10/31 22:13:50 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_lines(int fd, char *argv, t_env *e)
{
	int			size;
	char		*buf;
	char		**tabl;
	int			i;

	size = 0;
	buf = 0;
	i = 0;
	tabl = NULL;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("Error: Can't open, wrong fd.");
		exit(0);
	}
	while (get_next_line(fd, &buf) == 1)
	{
		size++;
		tabl = ft_strsplit(buf, ' ');
	}
	while (tabl && tabl[i])
		i++;
	close(fd);
	e->line = size;
	e->column = i;
}

t_point			**ft_alloc_struct(t_env *e)
{
	int			n;
	int			p;
	t_point		**tab1;
	t_point		*tab2;

	n = -1;
	p = 0;
	if (!(tab1 = (t_point **)malloc(sizeof(t_point *) * e->line)))
		return (0);
	if (!(tab2 = (t_point *)malloc(sizeof(t_point) * (e->column * e->line))))
		return (0);
	while (++n < e->line)
		tab1[n] = &tab2[n * e->column];
	return (tab1);
}

t_point			**ft_convert(int fd, char *argv, t_env *e)
{
	char		*buf;
	char		**buffer;
	t_point		**tmp;

	e->p = 0;
	e->n = 0;
	tmp = ft_alloc_struct(e);
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &buf) == 1)
	{
		buffer = ft_strsplit(buf, ' ');
		while (e->n < e->column)
		{
			tmp[e->p][e->n].z = ft_atoi(buffer[e->n]);
			tmp[e->p][e->n].x = e->n;
			tmp[e->p][e->n].y = e->p;
			e->n++;
		}
		e->p++;
		e->n = 0;
	}
	ft_strdel(&buf);
	return (tmp);
}

t_env			*ft_init_e(void)
{
	t_env		*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp->end = 0;
	tmp->move_up = 0;
	tmp->move_down = 0;
	tmp->move_left = 0;
	tmp->move_right = 0;
	tmp->x_move = 50;
	tmp->y_move = 50;
	tmp->z_move = 3;
	return (tmp);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_env		*e;

	fd = 0;
	if (argc == 2)
	{
		if (!(e = ft_init_e()))
			return (-1);
		ft_lines(fd, argv[1], e);
		e->tabl = ft_convert(fd, argv[1], e);
		assign_iso(e);
		if ((e->mlx = mlx_init()) == NULL)
			return (-1);
		e->img_str = mlx_new_image(e->mlx, WIDTH, HEIGHT);
		e->img_ptr = mlx_get_data_addr(e->img_str, &e->bpp, SIZEL, ENDIAN);
		if ((e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "fdf")) == NULL)
			return (-1);
		e->zoom = 50;
		draw_map(e);
		mlx_key_hook(e->win, ft_key_hook, e);
		mlx_loop(e->mlx);
	}
	else
		ft_putendl("Error: not enough or too many argument(s).");
	return (0);
}
