/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:16:01 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 15:16:25 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)src;
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(ptr));
	while (ptr[i] && i < (dstsize - 1))
	{
		dst[i] = ptr[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(ptr));
}
