/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 14:00:59 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_errors(t_var var, int *i, int *j)
{
	printf(MINISHELL ERRORS_EXP "\'%s\': ", var.key);
	printf(ERRORS_IDENTIFIER);
	exit_status = 1;
	(*j)++;
	(*i)--;
}

void export_increase(int *i, int *j)
{
	(*j)++;
	(*i)--;
	exit_status = 0;
}

char	**update_env(char **old, t_var var, bool quotes)
{
	char	**new;
	int		var_pos;

	if (var.key == NULL)
		return (old);
	var_pos = var_exist(old, var.key);
	if (var_pos != 0)
		new = update_var(old, var, var_pos, quotes);
	else
		new = add_var(old, var, quotes);
	return (new);
}

// compter les commandes pour export
int spaces_count(t_tprint tp)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] > 2)
			nbr++;
		else
		{
			nbr++;
			while (tp.tab[i] != NULL && tp.print[i + 1] < 3)
				i++;
		}
		if (tp.tab[i] != NULL)
			i++;
	}
	return (nbr);
}
