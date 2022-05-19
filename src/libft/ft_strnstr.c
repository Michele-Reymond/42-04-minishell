/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 09:36:10 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 15:57:33 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_c1(char n, char fh)
{
	if (n != '\0' && fh == n)
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *n, size_t l)
{
	size_t	l_n;
	size_t	i;
	size_t	j;
	char	*fh;

	i = 0;
	j = 0;
	fh = (char *)haystack;
	l_n = ft_strlen(n);
	if ((l_n == 0 || haystack == n) && (*n == 0))
		return (fh);
	if (l_n > l && *haystack == 0)
		return (0);
	while (fh[i] != '\0' && i < l)
	{
		j = 0;
		while (fh[i + j] != '\0' && ft_c1(n[j], fh[i + j]) == 1 && i + j < l)
			j++;
		if (j == l_n)
			return (fh + i);
		i++;
	}
	return (0);
}
