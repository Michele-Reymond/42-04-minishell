/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:57:55 by vroch             #+#    #+#             */
/*   Updated: 2022/08/13 11:34:14 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char const *s, char c)
{
	int		i;
	int		words;
	size_t	sep;

	i = 0;
	words = 0;
	sep = 0;
	if (s[i] && s[i] != c)
		words++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			words++;
		if (s[i] == c)
			sep++;
		i++;
	}
	if (s[i - 1] == c)
		words--;
	if (words <= 0)
		words = 1;
	if (sep == ft_strlen(s))
		words = 0;
	return (words);
}

static int	copywords(char **strtab, char const *s, char c, int words)
{
	int	len;
	int	i;
	int	y;

	len = 0;
	i = 0;
	y = 0;
	while (s[i] != '\0' && y < words)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			len++;
		}
		strtab[y] = (char *)malloc(sizeof(char) * (len + 1));
		if (!strtab[y])
			return (0);
		ft_strlcpy(strtab[y], &s[i - len], len + 1);
		y++;
	}
	return (y);
}

char	**ft_split(char const *s, char c)
{
	char	**strtab;
	int		y;
	int		words;

	y = 0;
	if (s == NULL)
		return (NULL);
	words = countwords(s, c);
	strtab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strtab)
		return (NULL);
	y = copywords(strtab, s, c, words);
	strtab[y] = 0;
	return (strtab);
}
