/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:27:52 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strldup(const char *src, size_t dstsize)
{
	size_t	i;
	char	*dst;
	char	*ptr;

	i = 0;
	if (dstsize == 0)
		return (NULL);
	ptr = (char *)src;
	dst = malloc(sizeof(char) * (dstsize + 1));
	if (dst == NULL)
		return (NULL);
	while (ptr[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = ptr[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}