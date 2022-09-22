/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 16:02:15 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a truct with redirections infos
t_redir	*stock_redir_infos(char **cmds)
{
	t_redir	*r;
	int		i;

	i = 0;
	r = malloc(sizeof(t_redir) * (tab_len(cmds) + 1));
	while (cmds[i] != NULL)
	{
		if (parse_for_redir_infos(cmds[i], &r[i], i))
			return (NULL);
		i++;
	}
	return (r);
}

//remove redirection part of the cmd
char	*stock_cmd_part(char **token, int pos)
{
	int		i;
	char	*tmp;
	char	*dst;
	char	*trimmed;

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

char	*which_redir_is_it(t_tprint tp, int i)
{
	char	*redir;

	redir = NULL;
	if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
		&& tp.tab[i][0] == '>' && ft_strlen(tp.tab[i]) == 1)
		redir = ft_strdup(">");
	else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
		&& tp.tab[i][0] == '>' && ft_strlen(tp.tab[i]) == 2)
		redir = ft_strdup(">>");
	else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
		&& tp.tab[i][0] == '<' && ft_strlen(tp.tab[i]) == 1)
		redir = ft_strdup("<");
	else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
		&& tp.tab[i][0] == '<' && ft_strlen(tp.tab[i]) == 2)
		redir = ft_strdup("<<");
	else if (tp.tab[i + 1] == NULL)
		redir = ft_strdup("");
	return (redir);
}

static int	make_r_dest(t_redir *r, t_tprint tp, int pos)
{
	char		*tmp;

	if (tp.tab[pos + 1] != NULL)
		tmp = ft_strdup(tp.tab[pos + 1]);
	else
	{
		printf("syntax error near unexpected token `%s'\n", r->redir);
		return (1);
	}
	r->dest = ft_strtrim(tmp, " ");
	free(tmp);
	return (0);
}

// for each cmd we parse the cmd with parsing master and stock infos
int	parse_for_redir_infos(char *cmd, t_redir *r, int index)
{
	t_tprint	tp;
	int			pos;
	int			i;

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
		if (make_r_dest(r, tp, pos))
			return (1);
		r->cmd = stock_cmd_part(tp.tab, pos);
	}
	free_tp(tp);
	return (0);
}
