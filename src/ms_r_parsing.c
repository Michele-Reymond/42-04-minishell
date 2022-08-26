/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/09 11:08:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a truct with redirections infos
t_redir *stock_redir_infos(char **cmds)
{
	t_redir *r;
	int i;

	i = 0;
	r = malloc(sizeof(t_redir) * (tab_len(cmds) + 1));
	while (cmds[i] != NULL)
	{
		parse_for_redir_infos(cmds[i], &r[i], i);
		i++;
	}
	return (r);
}

//remove redirection part of the cmd
char    *stock_cmd_part(char **token, int pos)
{
	int i;
	char *tmp;
	char *dst;
	char *trimmed;

	i = 0;
	dst = ft_strdup("");
	while (token[i] != NULL)
	{
		if (!(i == pos || i == pos + 1))
		{
			tmp = ft_strjoin(dst, token[i]);
			free(dst);
			dst = tmp;
			tmp = ft_strjoin(dst, " ");
			free(dst);
			dst = tmp;
		}
		i++;
	}
	trimmed = ft_strtrim(dst, " ");
	free(dst);
	return (trimmed);
}

char **rebuilt_cmds(t_redir *r, int len)
{
	char **cmds;
	int i;

	i = 0;
	cmds = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		cmds[i] = ft_strdup(r[i].cmd);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

char *which_redir_is_it(t_tprint tp, int i)
{
	char *redir;

	redir = NULL;
	if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) 
			&& tp.tab[i][0] == '>' && ft_strlen(tp.tab[i]) == 1)
		redir = ft_strdup(">");
	else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) 
			&& tp.tab[i][0] == '>' && ft_strlen(tp.tab[i]) == 2)
		redir = ft_strdup(">>");
	else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) 
			&& tp.tab[i][0] == '<' && ft_strlen(tp.tab[i]) == 1)
		redir = ft_strdup("<");
	else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) 
			&& tp.tab[i][0] == '<' && ft_strlen(tp.tab[i]) == 2)
		redir = ft_strdup("<<");
	else if (tp.tab[i + 1] == NULL)
		redir = ft_strdup("");
	return (redir);
}

// for each cmd we parse the cmd with parsing master and stock infos
void parse_for_redir_infos(char *cmd, t_redir *r, int index)
{
	t_tprint tp;
	char *tmp;
	int pos;
	int i;
	
	i = -1;
	tp = parsing_master(cmd);
	r->redir = NULL;
	while (tp.tab[++i] != NULL && r->redir == NULL)
		r->redir = which_redir_is_it(tp, i);
	r->index = index;
	if (*(r->redir) == '\0')
	{
		r->dest = ft_strdup("");
		r->cmd = ft_strdup(cmd);
	}
	else 
	{
		pos = var_exist(tp.tab, r->redir);
		tmp = ft_strdup(tp.tab[pos + 1]);
		r->dest = ft_strtrim(tmp, " ");
		free(tmp);
		r->cmd = stock_cmd_part(tp.tab, pos);
	}
	free_tp(tp);
}