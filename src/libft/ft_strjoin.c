/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:07:17 by vroch             #+#    #+#             */
/*   Updated: 2022/06/03 17:35:13 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len(char const *s1, char const *s2)
{
	size_t	len;

	len = (ft_strlen(s1) + ft_strlen(s2));
	if ((ft_strlen(s1) == 0) || (ft_strlen(s2) == 0))
		len = len - 1;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_len(s1, s2);
	ptr = malloc (sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		if (i <= ft_strlen(s1))
			ptr[i] = s1[j++];
		if (i >= ft_strlen(s1))
			ptr[i] = s2[k++];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
