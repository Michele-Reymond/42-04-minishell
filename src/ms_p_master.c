/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:18:10 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_splitted_cmds(char *cmd, t_tprint new)
{
	int		i;
	int		j;
	t_c		c;
	char	stock;

	i = 0;
	j = 0;
	stock = '\0';
	while (cmd[i] != '\0')
	{
		while (cmd[i] == ' ' || cmd[i] == '	')
			i++;
		copy_outside_quotes(cmd, &i, &j, new);
		c.i = i;
		c.j = j;
		if (copy_inside_quotes(cmd, &c, &stock, new))
			break ;
		i = c.i;
		j = c.j;
		j++;
	}
	new.tab[j] = NULL;
}

t_tprint	split_cmds(char *cmd, int tablen)
{
	t_tprint	new;

	new.tab = malloc(sizeof(char *) * (tablen + 1));
	if (new.tab == NULL)
	{
		new.print = NULL;
		return (new);
	}
	new.print = malloc(sizeof(int) * (tablen + 1));
	new.print[0] = tablen;
	create_splitted_cmds(cmd, new);
	return (new);
}

t_tprint	split_both_quotes(char *cmd)
{
	int			tablen;
	t_tprint	splitted;
	int			i;
	char		stock;

	i = 0;
	stock = '\0';
	tablen = count_quotes(cmd, stock, i);
	splitted = split_cmds(cmd, tablen);
	return (splitted);
}

void	create_tprint(t_tprint tmp, t_tprint tp)
{
	int	i;

	i = 0;
	while (tmp.tab[i] != NULL)
	{
		if (tmp.tab[i][0] == '\''
			&& tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\'')
			trim_single_and_tprint(tmp, &tp, i);
		else if (tmp.tab[i][0] == '\"'
				&& tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\"')
			trim_doubles_and_tprint(tmp, &tp, i);
		else if (tmp.tab[i][0] == '\"' || tmp.tab[i][0] == '\''
			|| tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\"'
			|| tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\'')
		{
			tp.tab[i] = ft_strdup(tmp.tab[i]);
			tp.print[i + 1] = -1;
		}
		else
			trim_and_tprint_else(tmp, &tp, i);
		i++;
	}
	tp.tab[i] = NULL;
}

// 0 : pour les string avec single quote
// 1 : pour les string avec double quotes
// 2 : pour les string avec aucune quotes
// 3 : pour les string avec single quote et espace après
// 4 : pour les string avec double quotes et espace après
// 5 : pour les tring avec aucune quotes et espace après
// utiliser display_tab_and_int(tp.print, tp.tab); pour afficher les 2
t_tprint	parsing_master(char *cmd)
{
	t_tprint	tmp;
	t_tprint	tp;

	tmp = split_both_quotes(cmd);
	tp.tab = malloc(sizeof(char *) * (tab_len(tmp.tab) + 1));
	tp.print = malloc(sizeof(int) * (tab_len(tmp.tab) + 1));
	tp.print[0] = tab_len(tmp.tab);
	create_tprint(tmp, tp);
	tabfree(tmp.tab);
	free(tmp.print);
	return (tp);
}
