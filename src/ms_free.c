/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:28:30 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/13 22:43:36 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tabs(t_tab *t, char **tab, char *str)
{
    if (t->env != NULL)
	    tabfree(t->env);
    if (t->exp != NULL)
	    tabfree(t->exp);
    if (t->p.cmds != NULL)
	    tabfree(t->p.cmds);
    if (tab != NULL)
	    tabfree(tab);
    if (str != NULL)
	    free(str);
}

void free_t_tab(t_tab *t)
{
    if (t->env != NULL)
	    tabfree(t->env);
    if (t->exp != NULL)
	    tabfree(t->exp);
    if (t->p.cmds != NULL)
	    tabfree(t->p.cmds);
}

void free_tabs_and_tp(t_tab *t, t_tprint tp, char *str)
{
    if (t->env != NULL)
	    tabfree(t->env);
    if (t->exp != NULL)
	    tabfree(t->exp);
    if (t->p.cmds != NULL)
	    tabfree(t->p.cmds);
    if (tp.tab != NULL)
	    tabfree(tp.tab);
    if (tp.print)
        free(tp.print);
    if (str != NULL)
	    free(str);
}

int free_tp_status_error(t_tprint tp)
{
    if (tp.tab != NULL)
	    tabfree(tp.tab);
    if (tp.print)
        free(tp.print);
    exit_status = 1;
    return (1);
}

void free_tp(t_tprint tp)
{
    if (tp.tab != NULL)
	    tabfree(tp.tab);
    if (tp.print)
    {
        free(tp.print);
        tp.print = NULL;
    }
}

void free_elem(t_echo elem)
{
    if (elem.args != NULL)
	    tabfree(elem.args);
    if (elem.vars != NULL)
	    tabfree(elem.vars);
    if (elem.spaces != NULL)
	    free(elem.spaces);
}

void ft_free(char *str)
{
    if (str != NULL)
    {
	    free(str);
        str = NULL;
    }
}