/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/03 16:37:39 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour le parsing voir l'onglet parsing de Notion

void	display_export(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

char	**update_env(char **old, t_var var, bool quotes)
{
	char	**new;
	int		var_pos;

	if (var.key == NULL)
		return (old);
	var_pos = var_exist(old, var.key);
	if (var_pos != 0)
		new = update_var(old, var, var_pos, quotes);
	else
		new = add_var(old, var, quotes);
	return (new);
}

t_tab	*ft_export(t_tab *t, char **token)
{
	t_var	*vartab;
	char	**tmp;
	char	**tmp2;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (tab_len(token) == 1)
		display_export(t->exp);
	else
	{
		vartab = malloc(sizeof(t_var) * tab_len(token) - 1);
		while (token[i])
		{
			vartab[j] = str_to_var(token[i]);
			i++;
			j++;
		}
		j = 0;
		while (i > 1)
		{
			tmp = update_env(t->env, vartab[j], false);
			tmp2 = update_env(t->exp, vartab[j], true);
			tabfree(t->env);
			tabfree(t->exp);
			t->env = tmp;
			t->exp = tabsort(tmp2);
			j++;
			i--;
		}
	}
	return (t);
}
