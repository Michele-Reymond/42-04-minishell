/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_tabsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:30:20 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/02 18:15:46 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	sort_caps(char **env, char **sorted)
// {
// 	char	alphabet;
// 	int		i;
// 	int		j;

// 	alphabet = 'A';
// 	j = -1;
// 	while (alphabet <= 'Z')
// 	{
// 		i = -1;
// 		while (env[++i])
// 		{
// 			if (env[i][0] == alphabet)
// 				sorted[++j] = ft_strdup(env[i]);
// 		}
// 		alphabet++;
// 	}
// 	return (j);
// }

// void	sort_small(char **env, char **sorted, int j)
// {
// 	char	alphabet;
// 	int		i;

// 	i = -1;
// 	alphabet = 'a';
// 	while (alphabet <= 'z')
// 	{
// 		i = -1;
// 		while (env[++i])
// 		{
// 			if (env[i][0] == alphabet)
// 				sorted[++j] = ft_strdup(env[i]);
// 		}
// 		alphabet++;
// 	}
// }

// char	**sort_env(char **env)
// {
// 	char	**sorted;
// 	// int		i;
// 	// int		j;
// 	// int     len;

// 	sorted = sorting_test(env);
// 	display_tab(sorted);
// 	exit(0);
// 	// j = -1;
// 	// len = tab_len(env);
// 	// sorted = malloc(sizeof(char *) * len + 1);
// 	// j = sort_caps(env, sorted);
// 	// i = -1;
// 	// while (env[++i])
// 	// {
// 	// 	if (!(env[i][0] >= 'A' && env[i][0] <= 'Z')
// 	// 			&& !(env[i][0] >= 'a' && env[i][0] <= 'z'))
// 	// 		sorted[++j] = ft_strdup(env[i]);
// 	// }
// 	// sort_small(env, sorted, j);
// 	// sorted[len] = NULL;
// 	return (sorted);
// }

char	**tabsort(char **tab)
{
	int len;
	char **tmp;
	char **new;
	int i;
	int j;

	i = 0;
	j = 0;
	len = tab_len(tab);
	new = tabdup(tab);
	tmp = malloc(sizeof(char) * tab_len(new) + 1);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if(ft_strncmp(new[i],new[j], ft_strlen(new[j]))>0){
				tmp[i] = malloc(sizeof(char) * ft_strlen(new[i]) + 1);
				tmp[i] = ft_strdup(new[i]);
				free(new[i]);
				new[i] = malloc(sizeof(char) * ft_strlen(new[j]));
				new[i] = ft_strdup(new[j]);
				free(new[j]);
				new[j] = malloc(sizeof(char) * ft_strlen(tmp[i]));
				new[j] = ft_strdup(tmp[i]);
			}
			j++;
		}
		i++;
	}
	free(tmp);

  return (new);
}
