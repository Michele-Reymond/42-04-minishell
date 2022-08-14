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

void free_tabs(t_tab *t, char **tab)
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

void free_vartab(t_var *vartab, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (vartab[i].key != NULL)
        {
            free(vartab[i].key);
            vartab[i].key = NULL;
        }
        if (vartab[i].value != NULL)
        {
            free(vartab[i].value);
            vartab[i].value = NULL;
        }
        i++;
    }
    if (vartab != NULL)
    {
        free(vartab);
        vartab = NULL;
    }
}

void free_t_redirs(t_redir r)
{
    if (r.dest != NULL)
    {
	    free(r.dest);
        r.dest = NULL;
    }
    if (r.redir != NULL)
	{
	    free(r.redir);
        r.redir = NULL;
    }
    if (r.cmd != NULL)
	{
	    free(r.cmd);
        r.cmd = NULL;
    }
}