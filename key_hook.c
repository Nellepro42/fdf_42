/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 20:23:51 by neprocur          #+#    #+#             */
/*   Updated: 2015/10/31 17:36:55 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			verif(t_env *e)
{
	int		result_one;
	int		result_two;

	e->line = 0;
	e->column = 0;
	while (e->line && e->column)
	{
		e->line++;
		e->column++;
	}
	result_one = e->line / 2;
	result_two = e->column / 2;
	if ((e->size / 2 == result_one) && (e->i / 2 == result_two))
		return (0);
	else
		return (-1);
}

void		center(t_env *e)
{
	e->center.y = e->line / 2;
	e->center.x = e->column / 2;
}
