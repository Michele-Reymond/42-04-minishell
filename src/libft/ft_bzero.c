/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:45:15 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 14:54:09 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*strc;

	i = 0;
	strc = (unsigned char *)str;
	while (i < n)
	{
		strc[i] = 0;
		i++;
	}
	return (str = strc);
}
