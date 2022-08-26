/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 14:46:47 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_check(t_var var)
{
	if (!(ft_isalpha(var.key[0]) || var.key[0] == '_'))
		return (1);
	return (0);
}

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(((ft_isalpha(str[i]) && i == 0) || str[i] == '_' || str[i] == '=')
				|| ((ft_isalnum(str[i]) && i > 0)
					|| str[i] == '_' || str[i] == '=')))
			return (1);
		i++;
	}
	return (0);
}

t_var	*create_vartab(int *i, char **token)
{
	t_var	*vartab;
	int		j;

	j = 0;
	vartab = malloc(sizeof(t_var) * (tab_len(token) - 1));
	while (token[*i])
	{
		vartab[j] = str_to_var(token[*i]);
		if (vartab[j].key == NULL || check_identifier(vartab[j].key))
		{
			vartab[j].key = ft_strdup(token[*i]);
			vartab[j].status = -1;
		}
		else if (var_check(vartab[j]))
			vartab[j].status = -1;
		else
			vartab[j].status = 0;
		(*i)++;
		j++;
	}
	return (vartab);
}

void	update_with_new_var(t_tab *t, t_var var, int *i, int *j)
{
	char	**tmp;
	char	**tmp2;

	tmp = update_env(t->env, var, false);
	tmp2 = update_env(t->exp, var, true);
	tabfree(t->env);
	tabfree(t->exp);
	t->env = tmp;
	t->exp = tabsort(tmp2);
	g_exit_status = 0;
	tabfree(tmp2);
	(*j)++;
	(*i)--;
}

t_tab	*unset(t_tab *t, t_tprint tp)
{
	char	**parsed;
	t_tab	*new_t;

	parsed = parsing_for_export(tp);
	new_t = unset_var(t, parsed);
	tabfree(parsed);
	return (new_t);
}
