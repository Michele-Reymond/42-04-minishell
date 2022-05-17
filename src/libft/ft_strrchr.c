/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:16:37 by vroch             #+#    #+#             */
/*   Updated: 2021/11/19 11:17:35 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	cc;

	cc = (char) c;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == cc)
			return ((void *) &s[len]);
		len--;
	}
	if (len == 0)
	{
		if (s[len] == cc)
			return ((void *) &s[len]);
		else
			return (NULL);
	}
	return ((void *) &s[len]);
}
