/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:57:55 by vroch             #+#    #+#             */
/*   Updated: 2022/06/22 15:47:40 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cpt_nbd(char const *s, char c)
{
	int	i;
	int	j;
	int	nbd;

	i = 0;
	j = 0;
	nbd = 0;
	if (c == '\0' && s[0] != '\0')
		return (2);
	if (s[0] == '\0')
		return (1);
	while (s[i] != '\0' && i < (int)ft_strlen(s))
	{
		if (s[i] == c)
			j = 0;
		else
		{
			j = 1;
			while (s[i] != '\0' && s[i] != c)
				i++;
			nbd = nbd + j;
		}
		i++;
	}
	return (nbd + 1);
}

static int	*ft_pt_lmax(char const *s, char c, int nbd)
{
	int	i;
	int	l;
	int	*lmax;
	int	lc;

	i = 0;
	l = 0;
	lc = 0;
	lmax = malloc(nbd * sizeof(int *));
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (lc != 0)
				lmax[l++] = lc;
			if (lc != 0)
				lc = 0;
		}
		else
			lc++;
		i++;
	}
	if (s[i - 1] != c)
		lmax[l] = lc;
	return (lmax);
}

static void	ft_rempl(char **ptr, char const *s, char c, int *lmax)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			ptr[j][k] = s[i];
			k++;
			if (k >= lmax[j])
			{
				ptr[j][k] = '\0';
				j++;
				k = 0;
			}
		}
		i++;
	}
	ptr[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		nbd;
	int		*lmax;

	if (s == 0)
		return (0);
	nbd = ft_cpt_nbd(s, c);
	ptr = malloc(nbd * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	lmax = ft_pt_lmax(s, c, nbd);
	i = 0;
	while (i < nbd - 1)
	{
		ptr[i] = malloc((lmax[i] + 1) * sizeof(char));
		if (ptr[i] == NULL)
			return (NULL);
		ptr[i] = ft_bzero (ptr[i], lmax[i] + 1);
		i++;
	}
	ft_rempl(ptr, s, c, lmax);
	ptr[i] = (NULL);
	free(lmax);
	return (ptr);
}
