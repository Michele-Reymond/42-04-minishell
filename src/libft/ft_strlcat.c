/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:55:21 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 15:16:59 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t		src_len;
	size_t		dest_len;
	size_t		pos;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	pos = n;
	while (*dest)
	{
		dest++;
		if (pos > 0)
			pos--;
	}
	while (*src && pos > 1)
	{
		*dest++ = *src++;
		pos--;
	}
	*dest = '\0';
	if (n == 0)
		return (src_len);
	if (n < dest_len)
		return (src_len + n);
	else
		return (dest_len + src_len);
}
