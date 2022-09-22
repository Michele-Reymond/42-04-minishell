/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_cmds_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 13:28:48 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_splits_r(char *str)
{
	int		nbr;
	int		*nbr1;
	int		*nbr2;

	nbr1 = check_redir(str, '>');
	nbr2 = check_redir(str, '<');
	nbr = nbr1[0] + nbr1[1] + nbr2[0] + nbr2[1];
	free(nbr1);
	free(nbr2);
	return (nbr);
}

char	*copy_redir_in(char c, int *i)
{
	char	*new;

	if (c == '<')
	{
		new = ft_strdup("<<");
		(*i)++;
	}
	else
		new = ft_strdup("<");
	return (new);
}

char	*copy_redir_out(char c, int *i)
{
	char	*new;

	if (c == '>')
	{
		new = ft_strdup(">>");
		(*i)++;
	}
	else
		new = ft_strdup(">");
	return (new);
}

char	**split_out_r(char *str)
{
	char	**new;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	new = malloc(sizeof(char *) * ((how_many_splits_r(str) * 2) + 1));
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\0' && str[i] != '>' && str[i] != '<')
			i++;
		if (i > start)
			new[j++] = ft_strldup(&str[start], i - start + 1);
		if (str[i] == '<')
			new[j++] = copy_redir_in(str[i + 1], &i);
		else if (str[i] == '>')
			new[j++] = copy_redir_out(str[i + 1], &i);
		i++;
	}
	new[j] = NULL;
	return (new);
}
