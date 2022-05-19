/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:18:49 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 09:34:10 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	if (src == 0 && dest == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
