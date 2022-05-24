/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/23 20:00:19 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour le parsing voir l'onglet parsing de Notion

void sort_env(char **env)
{
	char	alphabet;
	char	**sorted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	alphabet = 'A';
	while (env[i])
		i++;
	sorted = malloc(sizeof(char *) * i);
	while (alphabet != 'Z')
	{
		i = 0;
		while (env[i])
		{
			if (env[i][0] == alphabet)
			{
				sorted[j] = ft_strdup(env[i]);
				printf("env %d :%s\n", j, sorted[j]);
				j++;
			}
			i++;
		}
		alphabet++;
	}
	i = 0;
	while (env[i])
	{
		if (!(env[i][0] >= 'A' && env[i][0] <= 'Z'))
		{
			sorted[j] = ft_strdup(env[i]);
			printf("env %d :%s\n", j, sorted[j]);
			j++;
		}
		i++;
	}
}

t_hash	ft_export(char **args)
{
	t_hash	new_hash;

	new_hash.key = args[0];
	new_hash.value = args[1];
	return (new_hash);
}
