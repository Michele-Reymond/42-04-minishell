/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:36:46 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 13:49:53 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;
	char	cc;

	cc = (char) c;
	i = 0;
	ptr = NULL;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (ptr);
}
