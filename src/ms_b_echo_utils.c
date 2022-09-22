/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 11:43:26 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *str)
{
	int		i;
	char	*key;

	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '	'
		&& str[i] != '\'' && str[i] != '$' && str[i] != '=')
		i++;
	key = ft_strldup(&str[1], i);
	return (key);
}

char	*export_to_var(char *str)
{
	char	*var;

	while (*str != '\0' && *str != '=')
		str++;
	if (*str == '\0')
		var = ft_strdup("");
	else
	{
		str += 2;
		var = ft_strldup(str, ft_strlen(str));
	}
	return (var);
}

char	*copy_variables(char *tmp, char **vars, int j, t_tab t)
{
	char	*key;
	int		pos;

	key = find_key(tmp);
	pos = var_exist(t.exp, key);
	if (pos == 0)
		vars[j] = ft_strdup("");
	else
		vars[j] = export_to_var(t.exp[pos]);
	tmp++;
	tmp = ft_strchr(tmp, '$');
	free(key);
	return (tmp);
}

int	how_many_dollars(char **tab, int *print)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (tab[i] != NULL && i <= print[0])
	{
		if (print[i + 1] != 0 && print[i + 1] != 3)
			nbr = nbr + how_many_in_str(tab[i], '$');
		i++;
	}
	return (nbr);
}

int	*copy_spaces_tab(int *print)
{
	int	i;
	int	j;
	int	*new;

	i = 1;
	j = 2;
	new = malloc(sizeof(int) * print[0]);
	new[0] = print[0] - 1;
	while (i < print[0])
	{
		new[i] = print[j];
		i++;
		j++;
	}
	return (new);
}
