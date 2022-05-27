/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-tabsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:30:20 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 12:54:24 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_caps(char **env, char **sorted)
{
	char	alphabet;
	int		i;
	int		j;

	alphabet = 'A';
	j = -1;
	while (alphabet != 'Z')
	{
		i = -1;
		while (env[++i])
		{
			if (env[i][0] == alphabet)
				sorted[++j] = ft_strdup(env[i]);
		}
		alphabet++;
	}
	return (j);
}

void	sort_small(char **env, char **sorted, int j)
{
	char	alphabet;
	int		i;

	i = -1;
	alphabet = 'a';
	while (alphabet != 'z')
	{
		i = -1;
		while (env[++i])
		{
			if (env[i][0] == alphabet)
				sorted[++j] = ft_strdup(env[i]);
		}
		alphabet++;
	}
}

char	**sort_env(char **env)
{
	char	**sorted;
	int		i;
	int		j;
	int     len;

	j = -1;
	len = tab_len(env);
	sorted = malloc(sizeof(char *) * len);
	j = sort_caps(env, sorted);
	i = -1;
	while (env[++i])
	{
		if (!(env[i][0] >= 'A' && env[i][0] <= 'Z')
				&& !(env[i][0] >= 'a' && env[i][0] <= 'z'))
			sorted[++j] = ft_strdup(env[i]);
	}
	sort_small(env, sorted, j);
	return (sorted);
}
