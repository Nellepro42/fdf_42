/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:03:44 by neprocur          #+#    #+#             */
/*   Updated: 2015/10/31 18:32:56 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_key_hook(int keycode, t_env *e)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == H)
		e->y_move -= 30;
	if (keycode == B)
		e->y_move += 30;
	if (keycode == RIGHT)
		e->x_move += 30;
	if (keycode == LEFT)
		e->x_move -= 30;
	if (keycode == MORE)
	{
		if (e->zoom < 100)
			e->zoom += 2;
	}
	if (keycode == LESS)
	{
		if (e->zoom > 20)
			e->zoom -= 2;
	}
	draw_map(e);
	return (0);
}
