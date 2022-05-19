/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:22 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 09:33:38 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*strc;

	i = 0;
	strc = (unsigned char *)str;
	while (i < n)
	{
		strc[i] = c;
		i++;
	}
	return (str = strc);
}
