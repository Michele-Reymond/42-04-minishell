/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/30 19:26:06 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **check_varstr(char **tmp)
{
	char	**new;
	char 	**vars;
	int		nbr_vars;
	int		i;
	int		j;
	int		k;
	int		len;
	
	i = 0;
	j = 0;
	k = 0;
	len = how_many_in_tab(tmp, '$') + tab_len(tmp);
	new = malloc(sizeof(char *) * (len + 1));
	while (tmp[j])
	{
		k = 0;
		nbr_vars = how_many_in_str(tmp[j],  '$');
		if (ft_strchr(tmp[j], '$'))
		{
			vars = ft_split(tmp[j], '$');
			while (vars[k])
			{
				if (k == 0 && tab_len(vars) > nbr_vars)
					new[i] = vars[k];
				else if (k == 0 && tab_len(vars) == nbr_vars)
					new[i] = ft_strjoin("$", vars[k]);
				else
					new[i] = ft_strjoin("$ ", vars[k]);
				i++;
				k++;
			}
		}
		else
		{
			new[i] = ft_strdup(tmp[j]);
			i++;
		}
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
	free(tmp);
	return (token);
}

int	how_many_in_tab(char **str, char c)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr + how_many_in_str(str[i], c);
		i++;
	}
	return (nbr);
}

int	how_many_in_str(char *str, char c)
{
	char	*pos;
	int		i;

	i = 0;
	pos = ft_strchr(str, c);
	while (pos)
	{
		pos++;
		pos = ft_strchr(pos, c);
		i++;
	}
	return (i);
}
