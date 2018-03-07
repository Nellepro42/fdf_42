/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 16:41:19 by neprocur          #+#    #+#             */
/*   Updated: 2015/01/18 20:11:31 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			join_stk(char **str, char *stk, int ret)
{
	char			*ptr;

	stk[ret] = '\0';
	ptr = *str;
	*str = ft_strjoin(*str, stk);
	ft_strdel(&ptr);
}

int					get_next_line(int const fd, char **line)
{
	int				len;
	static char		*str[256];
	char			*ptr;
	char			*stk;
	int				ret;

	if (fd < 0 || BUFF_SIZE <= 0 || !line || !(stk = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	str[fd] = !str[fd] ? ft_strnew(1) : str[fd];
	while (!(ft_strchr(str[fd], 0x0a)) && (ret = read(fd, stk, BUFF_SIZE)) > 0)
		join_stk(&str[fd], stk, ret);
	if (ret == -1)
		return (-1);
	if (ret == 0 && !(ft_strchr(str[fd], 0x0a)))
	{
		*line = str[fd];
		str[fd] = NULL;
		return (((*line)[0] == '\0') ? 0 : 1);
	}
	len = ft_strchr(str[fd], 0x0a) - str[fd];
	*line = ft_strsub(str[fd], 0, len);
	ptr = str[fd];
	str[fd] = ft_strdup(ft_strchr(str[fd], 0x0a) + 1);
	ft_strdel(&ptr);
	return (1);
}
