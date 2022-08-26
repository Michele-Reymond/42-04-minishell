/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:32:08 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**multiredir_split(char **old, char *to_split)
{
	char	**splitted;
	char	**new;

	splitted = split_out_r(to_split);
	new = tabjoin(old, splitted);
	tabfree(splitted);
	return (new);
}

char	**multiredir_add_quotes(char **old, t_tprint tp, int i)
{
	char	*quoted;
	char	**new;

	if ((tp.print[i + 1] == 1 || tp.print[i + 1] == 4) && i != 0)
		quoted = add_quotes(tp.tab[i], '\"');
	else if ((tp.print[i + 1] == 0 || tp.print[i + 1] == 3) && i != 0)
		quoted = add_quotes(tp.tab[i], '\'');
	else
		quoted = ft_strdup(tp.tab[i]);
	new = add_to_tab(old, quoted);
	free(quoted);
	return (new);
}

char	**splitting_r_tp(t_tprint tp)
{
	char	**tmp;
	char	**last;
	int		i;

	i = 0;
	last = new_tab();
	while (tp.tab[i] != NULL)
	{
		if((how_many_in_str(tp.tab[i], '>') > 0
			|| how_many_in_str(tp.tab[i], '<') > 0) && (tp.print[i + 1] == 2 
			|| tp.print[i + 1] == 5) && ft_strlen(tp.tab[i]) > 1)
		{
			tmp = multiredir_split(last, tp.tab[i]);
			tabfree(last);
			last = tmp;
		}
		else
		{
			tmp = multiredir_add_quotes(last, tp, i);
			tabfree(last);
			last = tmp;
		}
		i++;
	}
	return (last);
}

char **a_redir_pro_cmd(char *cmd)
{
	t_tprint tp;
	char **splitted;
	char **new;

	tp = parsing_master(cmd);
	splitted = splitting_r_tp(tp);
	if (!ft_strncmp(splitted[0], ">", 1) || !ft_strncmp(splitted[0], "<", 1))
		new = split_w_starting_redir(splitted);
	else
		new = split_w_starting_cmd(splitted);
	free_tp(tp);
	tabfree(splitted);
	return (new);
}