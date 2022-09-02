/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_tabsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:30:20 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:09:42 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sorting_tab(int i, int j, char **new)
{
	char	*tmp;

	tmp = ft_strdup(new[i]);
	free(new[i]);
	new[i] = ft_strdup(new[j]);
	free(new[j]);
	new[j] = ft_strdup(tmp);
	free(tmp);
}

char	**tabsort(char **tab)
{
	int		len;
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = tab_len(tab);
	new = tabdup(tab);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(new[i], new[j], ft_strlen(new[j])) > 0)
				sorting_tab(i, j, new);
			j++;
		}
		i++;
	}
	return (new);
}

char	**copy_in_export(char **env)
{
	int		i;
	char	**export;
	t_var	*vartab;

	i = 0;
	export = malloc(sizeof(char *) * (tab_len(env) + 1));
	if (export == NULL)
		return (NULL);
	vartab = malloc(sizeof(t_var) * tab_len(env));
	if (vartab == NULL)
	{
		tabfree(export);
		return (NULL);
	}
	while (env[i] != NULL)
	{
		vartab[i] = str_to_var(env[i]);
		export[i] = var_to_str_with_quotes(vartab[i]);
		ft_free(vartab[i].key);
		ft_free(vartab[i].value);
		i++;
	}
	free(vartab);
	export[i] = NULL;
	return (export);
}

char	**make_export(char **env)
{
	char	**export;
	char	**tmp;

	export = copy_in_export(env);
	tmp = tabsort(export);
	tabfree(export);
	export = tmp;
	return (export);
}
