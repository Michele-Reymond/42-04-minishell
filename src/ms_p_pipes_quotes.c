/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_pipes_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 17:05:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *add_quotes(char *old, char quote)
{
	char *new;
	int i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(old) + 3));
	new[0] = quote;
	while (old[i] != '\0')
	{
		new[i + 1] = old[i];
		i++;
	}
	new[i + 1] = quote;
	new[i + 2] = '\0';
	return (new);
}

char *add_quotes_and_print(char quote, char *str)
{
	char	*quoted;

	if (quote == '\0')
		quoted = ft_strdup(str);
	else
		quoted = add_quotes(str, quote);
	return (quoted);
}

char *adding_quotes(t_tprint tp, int i)
{
	char	*quoted;

	if (tp.print[i + 1] == 1 && i != 0)
		quoted = add_quotes_and_print('\"', tp.tab[i]);
	else if (tp.print[i + 1] == 4 && i != 0)
		quoted = add_quotes_and_print('\"', tp.tab[i]);
	else if (tp.print[i + 1] == 0 && i != 0)
		quoted = add_quotes_and_print('\'', tp.tab[i]);
	else if (tp.print[i + 1] == 3 && i != 0)
		quoted = add_quotes_and_print('\'', tp.tab[i]);
	else if (tp.print[i + 1] == 5)
		quoted = add_quotes_and_print('\0', tp.tab[i]);
	else
		quoted = add_quotes_and_print('\0', tp.tab[i]);
	return (quoted);
}

char *join_strings(t_tprint tp, int pos, int start)
{
	int i;
	char *tmp2;
	char *tmp3;
	char *new;

	i = start;
	new = ft_strdup("");
	while (tp.tab[i] != NULL && i < pos)
	{
		tmp2 = ft_strjoin(new, tp.tab[i]);
		if (tp.tab[i + 1] != NULL && tp.print[i + 1] > 2)
		{
			tmp3 = ft_strjoin(tmp2, " ");
			free(new);
			free(tmp2);
			new = tmp3;
		}
		else
		{
			free(new);
			new = tmp2;
		}
		i++;
	}
	return (new);
}
