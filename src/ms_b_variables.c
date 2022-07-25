/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:28:42 by mreymond          #+#    #+#             */
/*   Updated: 2022/07/05 17:03:00 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// crer une variable
t_var	str_to_var(char *str)
{
	t_var	new_var;
	int		i;

	i = 0;
	new_var.key = NULL;
	new_var.value = NULL;
	if (!str || !(ft_isalpha(str[i]) != 0 || str[i] == '_'))
		return (new_var);
	while (str[i] && str[i] != '=')
		i++;
	new_var.key = malloc(sizeof(char) * i + 1);
	ft_strlcpy(new_var.key, str, i + 1);
	if (str[i] != '\0')
	{
		i++;
		new_var.value = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
		ft_strlcpy(new_var.value, &str[i], (ft_strlen(str) - i + 1));
	}
	else
		new_var.value = ft_strdup("");
	return (new_var);
}

// ajouter une variable à un tableau
char	**add_var(char **old, t_var var, bool quotes)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(old) + 2));
	while (old[i] != NULL)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	if (quotes)
		new[i] = var_to_str_with_quotes(var);
	else
		new[i] = var_to_str(var);
	i++;
	new[i] = NULL;
	return (new);
}

// enlever une variable à un tableau
t_tab	*unset_var(t_tab *t, char **token)
{
	char	**new;
	int		i;
	int 	j;
	int		k;
	int		ok;
	int 	len;

	i = 0;
	ok = 0;
	k = 0;
	j = 1;
	len = tab_len(t->env) + 1;
	while (token[j] != NULL)
	{
		if (check_identifier(token[j]))
		{
			printf(MINISHELL ERRORS_UNSET "\'%s\': ", token[j]);
			printf(ERRORS_IDENTIFIER);
			len--;
			ok = -1;
		}
		j++;
	}
	if (ok == -1)
		exit_status = 1;
	else
		exit_status = 0;
	new = malloc(sizeof(char *) * len);
	i = 0;
	while (t->env[i] != NULL)
	{
		j = 1;
		ok = 0;
		while (token[j] != NULL)
		{
			if (!ft_strncmp(t->env[i], token[j], ft_strlen(token[j])))
			{
				ok = 1;
				break ;
			}
			j++;
		}
		if (ok == 0)
		{
			new[k] = ft_strdup(t->env[i]);
			k++;
		}
		i++;
	}
	new[k] = NULL;
	tabfree(t->env);
	tabfree(t->exp);
	t->env = new;
	t->exp = tabsort(t->env);
	return (t);
}

char	**update_var(char **old, t_var var, int pos, bool quotes)
{
	char	**new;
	int		i;
	

	i = 0;
	(void) pos;
	new = malloc(sizeof(char *) * (tab_len(old) + 1));
	while (old[i] != NULL)
	{
		// VR. mise en commentaire
		//printf("%s\n",old[i]);

		if (!ft_strncmp(old[i], var.key, ft_strlen(var.key)))
		{
			if (quotes)
				new[i] = var_to_str_with_quotes(var);
			else
				new[i] = var_to_str(var);
		}
		else
			new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
