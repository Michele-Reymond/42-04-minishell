/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/01 17:13:56 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse the redirections caracteres > >> < <<
int	*check_redir(char *cmd, char redir)
{
	char	*tmp;
	int		*nbr;
	
	nbr = malloc(sizeof(int) * 2);
	nbr[0] = 0;
	nbr[1] = 0;
	tmp = ft_strchr(cmd, redir);
	while (tmp != NULL)
	{
		if (tmp + 1 && tmp + 2 && *(tmp + 1) == redir && *(tmp + 2) == redir)
		{
			printf(ERROR_UNEXPECTED_TOKEN);
			if (tmp + 3 && *(tmp + 3) == redir)
				printf("`%c%c'\n", redir, redir);
			else
				printf("`%c'\n", redir);
			nbr[0] = -1;
			nbr[1] = -1;
			return (nbr);
		}
		if (tmp + 1 && *(tmp + 1) == redir)
		{
			nbr[1]++;
			cmd = tmp;
			tmp += 2;
		}
		else if (tmp && *tmp == redir)
			if (*(tmp + 1) != redir && *(tmp - 1) != redir)
			{
				nbr[0]++;
				cmd = tmp;
				tmp++;
			}
		tmp = ft_strchr(tmp, redir);
	}
	return (nbr);
}

t_parse	stock_parsing_infos(char *cmd)
{
	t_parse	p;
	int		*nbr1;
	int		*nbr2;
	
	p.redir_in = 0;
	p.redir_out = 0;
	p.redir_in_d = 0;
	p.redir_out_d = 0;
	p.pipes = how_many_in_str(cmd, '|');
	p.nbr_cmd = p.pipes + 1;
	p.double_q = how_many_in_str(cmd, '\"');
	p.single_q = how_many_in_str(cmd, '\'');
	p.dollar = how_many_in_str(cmd, '$');
	nbr1 = check_redir(cmd, '>');
	p.redir_out = nbr1[0];
	p.redir_out_d = nbr1[1];
	nbr2 = check_redir(cmd, '<');
	p.redir_in = nbr2[0];
	p.redir_in_d = nbr2[1];
	return (p);
}

int	pre_parsing_errors(char *cmd, t_parse p)
{
	(void) cmd;
	if (!(p.redir_in >= 0 && p.redir_out >= 0))
		return (1);
	if (p.double_q % 2 != 0)
	{
		printf(ERROR_QUOTES);
		return (1);
	}
	if (p.single_q % 2 != 0)
	{
		printf(ERROR_QUOTES);
		return (1);
	}
	return (0);
}

// créer un tableau de commandes
char	**clean_cmds(char *cmd, t_parse p)
{
	char	**cmds;
	char	**tmp;
	int		i;

	i = 0;
	(void) p;
	tmp = ft_split(cmd, '|');
	cmds = malloc(sizeof(char *) * tab_len(tmp) + 1);
	while (tmp[i])
	{
		cmds[i] = ft_strtrim(tmp[i], " ");
		i++;
	}
	cmds[i] = NULL;
	tabfree(tmp);
	return (cmds);
}

int	monitor(char *cmd, t_tab *t)
{
	t_parse	p;
	
	(void) t;
	p = stock_parsing_infos(cmd);
	if (pre_parsing_errors(cmd, p))
		return (1);
	p.cmds = clean_cmds(cmd, p);

	// TO DO > faire une fonction qui verifie les commandes

	// printf("%s\n", cmd);
	// printf("< : %d\n", p.redir_in);
	// printf("<< : %d\n", p.redir_in_d);
	// printf("> : %d\n", p.redir_out);
	// printf(">> : %d\n", p.redir_out_d);
	// printf("| : %d\n", p.pipes);
	
	if (tab_len(p.cmds) == 1)
		launch_cmds(p.cmds[0], t);
	return (0);
}

int	launch_cmds(char *cmd, t_tab *t)
{
	char	**token;

	token = tokenize(
		cmd);
	if (!ft_strncmp(cmd, "cd", 2))
		ms_b_cd(cmd);
	else if (!ft_strncmp(cmd, "pwd", 3))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo(token, *t);
	else if (!ft_strncmp(cmd, "export", 6))
		t->env = ft_export(t->env, token);
	// else if (!ft_strncmp(cmd, "unset", 5))
	// 	t->env = remove_var(t->env, token);
	else if (!ft_strncmp(cmd, "env", 3))
		display_tab(t->env);
	else
		ms_b_other(cmd);
	return (0);
}