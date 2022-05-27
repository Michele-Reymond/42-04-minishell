/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-var-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:49:03 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 11:53:04 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_to_str(t_var *var)
{
	char	*varstr;
	char	*tmp;

	tmp = ft_strjoin("=", var->value);
	varstr = ft_strjoin(var->key, tmp);
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
