/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_monitor_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 17:08:06 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**clean_quotes_token(char **token, t_parse p)
{
	char	**new;
	int		i;

	i = 0;
	if (p.double_q == 0 && p.single_q == 0)
	{
		new = tabdup(token);
		return (new);
	}
	new = malloc(sizeof(char *) * (tab_len(token) + 1));
	while (token[i] != NULL)
	{
		if (*token[i] == '\0')
			new[i] = ft_strdup(" ");
		else
			new[i] = ft_strtrim(token[i], "\"");
		i++;
	}
	new[i] = NULL;
	return (new);
}

int check_closed_quotes(t_tprint tp)
{
	int i;

	i = 1;
	while (i <= tp.print[0])
	{
		if(tp.print[i] == -1)
		{
			printf(ERROR_QUOTES);
			return (1);
		}
		i++;
	}
	return (0);
}