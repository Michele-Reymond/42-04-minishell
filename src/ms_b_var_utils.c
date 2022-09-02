/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_var_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:49:03 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/09 10:19:19 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_to_str(t_var var)
{
	char	*varstr;
	char	*tmp;

	if (*var.value != '\0')
		tmp = ft_strjoin("=", var.value);
	else
		tmp = ft_strdup("");
	varstr = ft_strjoin(var.key, tmp);
	free(tmp);
	return (varstr);
}

char	*var_to_str_with_quotes(t_var var)
{
	char	*varstr;
	char	*tmp;
	char	*tmp2;

	if (*var.value != '\0')
	{
		tmp2 = ft_strjoin(var.value, "\"");
		tmp = ft_strjoin("=\"", tmp2);
		free(tmp2);
	}
	else
		tmp = ft_strdup("");
	varstr = ft_strjoin(var.key, tmp);
	free(tmp);
	return (varstr);
}

int	var_exist(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (0);
}

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
