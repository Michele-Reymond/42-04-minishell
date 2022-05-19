/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 08:03:53 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 14:05:08 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_char;
	const unsigned char	*s2_char;
	size_t				i;

	s1_char = (const unsigned char *)s1;
	s2_char = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_char[i] != s2_char[i])
		{
			return ((s1_char[i] - s2_char[i]));
		}
		i++;
	}
	return (0);
}
