/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_tabsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:30:20 by mreymond          #+#    #+#             */
/*   Updated: 2022/07/28 12:25:00 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void sorting_tab(int i, int j, char **new, char **tmp)
{
	tmp[i] = malloc(sizeof(char) * ft_strlen(new[i]) + 1);
	tmp[i] = ft_strdup(new[i]);
	free(new[i]);
	new[i] = malloc(sizeof(char) * ft_strlen(new[j]));
	new[i] = ft_strdup(new[j]);
	free(new[j]);
	new[j] = malloc(sizeof(char) * ft_strlen(tmp[i]));
	new[j] = ft_strdup(tmp[i]);
}

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
			if (ft_strncmp(new[i],new[j], ft_strlen(new[j])) > 0)
				sorting_tab(i, j, new, tmp);
			j++;
		}
		i++;
	}
	free(tmp);
	return (new);
}

char	**make_export(char **env)
{
	int		i;
	char	**export;
	t_var	*vartab;

	i = 0;
	export = malloc(sizeof(t_var) * tab_len(env) + 1);
	vartab = malloc(sizeof(t_var) * tab_len(env));
	while (env[i] != NULL)
	{
		vartab[i] = str_to_var(env[i]);
		export[i] = var_to_str_with_quotes(vartab[i]);
		i++;
	}
	export[i] = NULL;
	export = tabsort(export);
	return (export);
}
