/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:32:47 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 14:24:21 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;
	int		i;

	len = ft_strlen(s1) + 1;
	ptr = malloc(len * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	if (len > 0)
	{
		while (s1[i] != '\0')
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[i] = '\0';
	}
	else
	{
		ptr[i] = '\0';
	}
	return (ptr);
}
