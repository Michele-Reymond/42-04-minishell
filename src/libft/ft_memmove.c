/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:17:09 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 13:44:16 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	s = src;
	d = dest;
	if (dest == src)
		return (dest);
	if (s < d)
	{
		while (n--)
			*(d + n) = *(s + n);
		return (dest);
	}
	while (n--)
		*d++ = *s++;
	return (dest);
}
