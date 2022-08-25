/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:59:26 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_multi_pipes_cmds(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != 0)
	{
		if (how_many_in_str(tp.tab[i], '|') > 0 && (tp.print[i + 1] == 2 
			|| tp.print[i + 1] == 5) && ft_strlen(tp.tab[i]) > 1)
		{
			nbr += how_many_in_str(tp.tab[i], '|');
			if (tp.tab[i][ft_strlen(tp.tab[i]) - 1] != '|' && tp.tab[i][0] != '|')
				nbr++;
			if (tp.tab[i][ft_strlen(tp.tab[i]) - 1] == '|' && tp.tab[i][0] == '|')
				nbr--;
			nbr += how_many_in_str(tp.tab[i], '|');
		}
		i++;
	}
	return (nbr);
}

char **split_out_multipipes(char *str, int nbr, int start, int i)
{
	char **new;
	int j;

	j = 0;
	new = malloc(sizeof(char *) * (nbr + 1));
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\0' && str[i] != '|')
			i++;
		if (i > start)
		{
			new[j] = ft_strldup(&str[start], i - start + 1);
			j++;
		}
		if (str[i] == '|')
		{
			new[j] = ft_strdup("|");;
			j++;
		}
		if (str[i] != '\0')
			i++;
	}
	new[j] = NULL;
	return (new);
}

char **split_out(char *str)
{
	char **new;
	int nbr;

	nbr = how_many_splits(str);
	new = split_out_multipipes(str, nbr, 0, 0);
	return (new);
}

int	multipipes_split(t_tprint tp, t_tprint *last, int i, int j)
{
	char	**splitted;
	char	**tmp;
	int		k;

	splitted = split_out(tp.tab[i]);
	tmp = tabjoin(last->tab, splitted);
	k = 0;
	while (k < tab_len(splitted) - 1)
	{
		last->print[j] = 2;
		j++;
		k++;
	}
	if (tp.print[i + 1] == 2)
		last->print[j] = 2;
	else
		last->print[j] = 5;
	j++;
	tabfree(last->tab);
	tabfree(splitted);
	last->tab = tmp;
	return (j);
}

int	onepipes_split(t_tprint tp, t_tprint *last, int i, int j)
{
	char	**tmp;
	char	*quoted;

	quoted = adding_quotes(tp, i);
	if (tp.print[i + 1] == 1 && i != 0)
		last->print[j] = 1;
	else if (tp.print[i + 1] == 4 && i != 0)
		last->print[j] = 4;
	else if (tp.print[i + 1] == 0 && i != 0)
		last->print[j] = 0;
	else if (tp.print[i + 1] == 3 && i != 0)
		last->print[j] = 3;
	else if (tp.print[i + 1] == 5)
		last->print[j] = 5;
	else
		last->print[j] = 2;
	tmp = add_to_tab(last->tab, quoted);
	tabfree(last->tab);
	free(quoted);
	quoted = NULL;
	last->tab = tmp;
	tmp = NULL;
	return (j + 1);
}
