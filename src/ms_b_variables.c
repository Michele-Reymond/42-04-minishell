/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:28:42 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/13 09:57:26 by mreymond         ###   ########.fr       */
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
	new_var.key = malloc(sizeof(char) * (i + 1));
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

int check_unset(char **token, int *len)
{
	int j;
	int ok;

	ok = 0;
	j = 1;
	while (token[j] != NULL)
	{
		if (check_identifier(token[j]))
		{
			printf(MINISHELL ERRORS_UNSET "\'%s\': ", token[j]);
			printf(ERRORS_IDENTIFIER);
			(*len)--;
			ok = -1;
		}
		j++;
	}
	return (ok);
}

int check_if_exist(char **token, char *env)
{
	int ok;
	int j;

	ok = 0;
	j = 1;
	while (token[j] != NULL)
	{
		if (!ft_strncmp(env, token[j], ft_strlen(token[j])))
		{
			ok = 1;
			break ;
		}
		j++;
	}
	return (ok);
}

char **rebuilt_env(int len, char **token, t_tab *t)
{
	int i;
	int ok;
	int k;
	char **new;

	i = 0;
	k = 0;
	new = malloc(sizeof(char *) * len);
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
	int 	len;

	len = tab_len(t->env) + 1;
	ok = check_unset(token, &len);
	if (ok == -1)
		exit_status = 1;
	else
		exit_status = 0;
	new = rebuilt_env(len, token, t);
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
