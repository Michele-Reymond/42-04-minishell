/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:28:30 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 14:33:02 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tabs(t_tab *t, char **tab)
{
	if (t->env != NULL)
		tabfree(t->env);
	if (t->exp != NULL)
		tabfree(t->exp);
	if (t->p.cmds != NULL)
		tabfree(t->p.cmds);
	if (tab != NULL)
		tabfree(tab);
}

void	free_t_tab(t_tab *t)
{
	if (t->env != NULL)
		tabfree(t->env);
	if (t->exp != NULL)
		tabfree(t->exp);
	if (t->p.cmds != NULL)
		tabfree(t->p.cmds);
}

int	free_tp_status_error(t_tprint tp)
{
	if (tp.tab != NULL)
		tabfree(tp.tab);
	if (tp.print)
		free(tp.print);
	g_exit_status = 1;
	return (1);
}

void	free_tp(t_tprint tp)
{
	if (tp.tab != NULL)
		tabfree(tp.tab);
	if (tp.print)
	{
		free(tp.print);
		tp.print = NULL;
	}
}

void	free_elem(t_echo elem)
{
	if (elem.args != NULL)
		tabfree(elem.args);
	if (elem.vars != NULL)
		tabfree(elem.vars);
	if (elem.spaces != NULL)
		free(elem.spaces);
}
