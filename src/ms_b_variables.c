/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:28:42 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 12:12:39 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	str_to_var(char *str)
{
	t_var	new_var;
	int		i;

	i = 0;
	new_var.key = NULL;
	new_var.value = NULL;
	if (!str || !(ft_isalpha(str[i]) != 0 || str[i] == '_'))
		return (new_var);
	while (str[i] && str[i] != '=' && (ft_isalnum(str[i]) != 0 || str[i] == '_'))
		i++;
	if (str[i] != '=')
		return (new_var);
	new_var.key = malloc(sizeof(char) * i + 1);
	ft_strlcpy(new_var.key, str, i + 1);
	i++;
	new_var.value = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	ft_strlcpy(new_var.value, &str[i], (ft_strlen(str) - i + 1));
	return (new_var);
}

char	**add_var(char **old, t_var *var)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(old) + 2));
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = var_to_str(var);
	i++;
	new[i] = NULL;
	return (new);
}

char	**remove_var(char **old, t_var *var)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(old) + 1));
	while (old[i])
	{
		if (ft_strncmp(old[i], var->key, ft_strlen(var->key)))
			new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**update_var(char **old, t_var *var, int pos)
{
	char	*tmp;

	tmp = old[pos];
	old[pos] = var_to_str(var);
	free(tmp);
	return (old);
}
