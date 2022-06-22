/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:35:25 by vroch             #+#    #+#             */
/*   Updated: 2022/06/22 15:07:22 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_check_ar(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		ko;

	i = ft_strlen(s1) - 1;
	while (i != 0)
	{
		j = 0;
		ko = 0;
		while (j < ft_strlen(set))
		{
			if (set[j] == s1[i])
				ko = 1;
			j++;
		}
		if (ko == 0)
		{
			i++;
			return (i);
		}
		i--;
	}
	return (0);
}

static int	ft_check_av(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		ko;

	i = 0;
	while (i <= ft_strlen(s1))
	{
		j = 0;
		ko = 0;
		while (j < ft_strlen(set))
		{
			if (set[j] == s1[i])
				ko = 1;
			j++;
		}
		if (ko == 0)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		pos_ar;
	int		pos_av;
	int		lg;
	int		i;

	if (s1 == 0 || set == 0)
		return (0);
	pos_ar = ft_check_ar(s1, set);
	pos_av = ft_check_av(s1, set);
	if (pos_ar == 0)
		lg = 0;
	else
		lg = pos_ar - pos_av;
	ptr = malloc(lg + 1 * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i <= pos_ar - pos_av - 1)
	{
		ptr[i] = s1[pos_av + i];
		i++;
	}	
	ptr[i] = '\0';
	return (ptr);
}
