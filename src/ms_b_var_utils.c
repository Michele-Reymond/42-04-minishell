/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_var_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:49:03 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/03 15:12:20 by mreymond         ###   ########.fr       */
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
