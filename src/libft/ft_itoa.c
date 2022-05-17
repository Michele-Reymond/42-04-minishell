/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:05:54 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 15:32:33 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

static int	ft_nbc(int n)
{
	int			nbc;
	long int	nlong;

	nbc = 0;
	nlong = (long)n;
	if (n < 0)
	{
		nbc++;
		nlong = nlong * -1;
	}
	if (n == 0)
		return (1);
	while (nlong != 0)
	{
		nbc++;
		nlong = nlong / 10;
	}
	return (nbc);
}

char	*ft_itoa(int n)
{
	long int	res;
	int			nbc;
	char		*ptr;

	nbc = ft_nbc(n);
	ptr = malloc (nbc + 1 * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	res = 0;
	res = (long)n;
	ptr[nbc] = '\0';
	nbc--;
	if (res < 0)
		ptr[0] = '-';
	if (res < 0)
		res = res * -1;
	if (res == 0)
		ptr[nbc] = '0';
	while (res != 0)
	{
		ptr[nbc--] = ((res % 10) + '0');
		res = res / 10;
	}
	return (ptr);
}
