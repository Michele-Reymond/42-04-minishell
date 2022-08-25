/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:08:16 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *convert_var(int *k, int *i, int nbr_vars, char **vars)
{
	char	*new;

	if (k == 0 && tab_len(vars) > nbr_vars)
		new = vars[*k];
	else if (k == 0 && tab_len(vars) == nbr_vars)
		new = ft_strjoin("$", vars[*k]);
	else
		new = ft_strjoin("$ ", vars[*k]);
	(*i)++;
	(*k)++;
	return (new);
}

char **check_varstr(char **tmp)
{
	char	**new;
	char 	**vars;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * 
		(how_many_in_tab(tmp, '$') + tab_len(tmp) + 1));
	while (tmp[j] != NULL)
	{
		k = 0;
		if (ft_strchr(tmp[j], '$'))
		{
			vars = ft_split(tmp[j], '$');
			while (vars[k] != NULL)
				new[i] = convert_var(&k, &i, how_many_in_str(tmp[j], '$'), vars);
		}
		else
			new[i++] = ft_strdup(tmp[j]);
		j++;
	}
	new[i] = NULL;
	return (new);
}

char	**tokenize(char *buff)
{
	char	**token;
	char	**tmp;
	char	*pos;

	if (buff == NULL)
		return (new_tab());
	pos = ft_strchr(buff, '\t');
	while (pos)
	{
		*pos = ' ';
		pos = ft_strchr(pos, '\t');
	}
	tmp = ft_split(buff, ' ');
	token = check_varstr(tmp);
	tabfree(tmp);
	return (token);
}
