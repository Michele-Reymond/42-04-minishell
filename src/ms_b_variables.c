/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:28:42 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 12:39:14 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exist(char **token, char *env)
{
	int	ok;
	int	j;

	ok = 0;
	j = 1;
	while (token[j] != NULL)
	{
		if ((token[j][0] != '\0')
			&& !ft_strncmp(env, token[j], ft_strlen(token[j])))
		{
			ok = 1;
			break ;
		}
		j++;
	}
	return (ok);
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
