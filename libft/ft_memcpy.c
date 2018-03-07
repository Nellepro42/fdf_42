/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 12:42:51 by neprocur          #+#    #+#             */
/*   Updated: 2014/12/13 20:56:46 by neprocur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;

	a = (char *)dst;
	if (ft_poney(dst, src, n) == 1)
		return (ft_memmove(a, src, n));
	return (ft_strncpy(a, src, n));
}
