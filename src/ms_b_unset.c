/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 12:36:31 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		g_exit_status = 1;
		return (1);
	}
	while (str[i] != '\0')
	{
		if (!(((ft_isalpha(str[i]) && i == 0) || str[i] == '_')
				|| ((ft_isalnum(str[i]) && i > 0) || str[i] == '_')))
			return (1);
		i++;
	}
	return (0);
}

int	check_unset(char **token)
{
	int	j;
	int	ok;

	ok = 0;
	j = 1;
	while (token[j] != NULL)
	{
		if (check_unset_identifier(token[j]))
		{
			printf(MINISHELL ERRORS_UNSET "\'%s\': ", token[j]);
			printf(ERRORS_IDENTIFIER);
			ok = -1;
		}
		j++;
	}
	return (ok);
}

int	how_much_to_unset(char **token, t_tab *t)
{
	int		i;
	int		minus;
	int		ok;

	i = 0;
	minus = 0;
	while (t->env[i] != NULL)
	{
		ok = check_if_exist(token, t->env[i]);
		if (ok != 0)
			minus++;
		i++;
	}
	return (minus);
}

char	**rebuilt_env(int len, char **token, t_tab *t)
{
	int		i;
	int		ok;
	int		k;
	char	**new;
	int		minus;

	i = 0;
	k = 0;
	minus = how_much_to_unset(token, t);
	new = malloc(sizeof(char *) * (len - minus));
	while (t->env[i] != NULL)
	{
		ok = check_if_exist(token, t->env[i]);
		if (ok == 0)
			new[k++] = ft_strdup(t->env[i]);
		i++;
	}
	new[k] = NULL;
	return (new);
}

// enlever une variable à un tableau
t_tab	*unset_var(t_tab *t, char **token)
{
	char	**new;
	int		ok;
	int		len;

	len = tab_len(t->env) + 1;
	ok = check_unset(token);
	if (ok == -1)
		g_exit_status = 1;
	else
		g_exit_status = 0;
	new = rebuilt_env(len, token, t);
	tabfree(t->env);
	tabfree(t->exp);
	t->env = new;
	t->exp = make_export(t->env);
	return (t);
}
