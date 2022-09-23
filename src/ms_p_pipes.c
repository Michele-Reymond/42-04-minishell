/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 14:08:13 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tprint	init_splitted_pipes(t_tprint tp)
{
	int			pipes;
	t_tprint	last;

	last.tab = new_tab();
	pipes = count_multi_pipes_cmds(tp);
	last.print = malloc(sizeof(char *) * (pipes + tp.print[0] + 1));
	last.print[0] = pipes + tp.print[0];
	return (last);
}

t_tprint	split_pipes_phase_1(t_tprint tp)
{
	int			i;
	int			j;
	char		**tmp;
	t_tprint	last;

	i = 0;
	j = 1;
	last = init_splitted_pipes(tp);
	while (tp.tab[i] != NULL)
	{
		if (how_many_in_str(tp.tab[i], '|') > 0
			&& (tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
			&& ft_strlen(tp.tab[i]) > 1)
			j = multipipes_split(tp, &last, i, j);
		else
			j = onepipes_split(tp, &last, i, j);
		i++;
	}
	tmp = add_to_tab(last.tab, "");
	tabfree(last.tab);
	last.tab = tmp;
	last.tab[tab_len(tmp)] = NULL;
	return (last);
}

int	check_doubles_pipes(t_tprint tp)
{
	int	i;

	i = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.tab[i][0] == '|' && tp.tab[i + 1][0] == '|'
			&& (tp.print[i + 1] == 2))
		{
			printf(ERROR_UNEXPECTED_TOKEN "\'||\'\n");
			g_exit_status = 258;
			return (1);
		}
		else if ((tp.tab[i][0] == '|' && tab_len(tp.tab) == 2)
			|| (tp.tab[i][0] == '|' && tp.tab[i + 1][0] == '|'
			&& tp.print[i + 1] == 5))
		{
			printf(ERROR_UNEXPECTED_TOKEN "\'|\'\n");
			g_exit_status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**split_pipes_phase_2(t_tprint splitted, int pipes)
{
	int		i;
	int		j;
	int		start;
	char	**new;

	i = 0;
	j = 0;
	start = 0;
	new = malloc(sizeof(char *) * (pipes + 2));
	while (splitted.tab[i] != NULL)
	{
		start = i;
		while (splitted.tab[i] != NULL && !(splitted.tab[i][0] == '|'
			&& ft_strlen(splitted.tab[i]) == 1))
			i++;
		if (i > start)
		{
			new[j] = join_strings(splitted, i, start);
			j++;
		}
		if (splitted.tab[i] != NULL)
			i++;
	}
	new[j] = NULL;
	return (new);
}

char	**split_pipes(t_tprint tp, int pipes)
{
	t_tprint	splitted;
	char		**new;

	if (*tp.tab && *tp.tab[0] == '|' && ft_strlen(tp.tab[0]) == 1)
	{
		printf(ERROR_UNEXPECTED_TOKEN "\'|\'\n");
		g_exit_status = 258;
		return (NULL);
	}
	else if (*tp.tab && *tp.tab[0] == '|' && ft_strlen(tp.tab[0]) == 2
		&& tp.tab[0][1] == '|')
	{
		printf(ERROR_UNEXPECTED_TOKEN "\'||\'\n");
		g_exit_status = 258;
		return (NULL);
	}
	splitted = split_pipes_phase_1(tp);
	if (check_doubles_pipes(splitted))
		return (NULL);
	new = split_pipes_phase_2(splitted, pipes);
	free_tp(splitted);
	return (new);
}
