/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:36:46 by vroch             #+#    #+#             */
/*   Updated: 2022/05/31 14:20:15 by mreymond         ###   ########.fr       */
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
