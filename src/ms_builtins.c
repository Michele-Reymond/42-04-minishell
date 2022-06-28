/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/28 12:04:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse the redirections caracteres > >> < <<
// return a int tab :
// nbr[0] : nbr of simple redir (> or <)
// nbr[1] : nbr of double redir (>> or <<)
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

int count_pipes(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 2)
			nbr += how_many_in_str(tp.tab[i], '|');
		i++;
	}
	return (nbr);
}

int count_doubles(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 1)
			nbr++;
		i++;
	}
	return (nbr);
}

int count_singles(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 0)
			nbr++;
		i++;
	}
	return (nbr);
}

int count_dollar(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] != 0)
			nbr += how_many_in_str(tp.tab[i], '$');
		i++;
	}
	return (nbr);
}


t_parse	stock_parsing_infos(t_tprint tp)
{
	t_parse	p;
	// int		*nbr1;
	// int		*nbr2;
	
	p.pipes = count_pipes(tp);
	p.nbr_cmd = p.pipes + 1;
	p.double_q = count_doubles(tp);
	p.single_q = count_singles(tp);
	p.dollar = count_dollar(tp);
	printf("%d\n", p.dollar);
	exit(0);
	// nbr1 = check_redir(cmd, '>');
	// p.redir_out = nbr1[0];
	// p.redir_out_d = nbr1[1];
	// nbr2 = check_redir(cmd, '<');
	// p.redir_in = nbr2[0];
	// p.redir_in_d = nbr2[1];
	// p.redir = p.redir_in + p.redir_in_d + p.redir_out + p.redir_out_d;
	return (p);
}

// t_parse	stock_parsing_infos(char *cmd)
// {
// 	t_parse	p;
// 	int		*nbr1;
// 	int		*nbr2;
	
// 	p.pipes = how_many_in_str(cmd, '|');
// 	p.nbr_cmd = p.pipes + 1;
// 	p.double_q = how_many_in_str(cmd, '\"');
// 	p.single_q = how_many_in_str(cmd, '\'');
// 	p.dollar = how_many_in_str(cmd, '$');
// 	nbr1 = check_redir(cmd, '>');
// 	p.redir_out = nbr1[0];
// 	p.redir_out_d = nbr1[1];
// 	nbr2 = check_redir(cmd, '<');
// 	p.redir_in = nbr2[0];
// 	p.redir_in_d = nbr2[1];
// 	p.redir = p.redir_in + p.redir_in_d + p.redir_out + p.redir_out_d;
// 	return (p);
// }

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

// créer un tableau de commandes clean
char	**clean_cmds(char *cmd, t_parse p)
{
	char	**cmds;
	// char	**tmp;
	(void) p;
	
	cmds = clean_spaces(cmd);
	// autres clean a faire?
	return (cmds);
}

// créer un tableau de commandes sans les espaces
char	**clean_spaces(char *cmd)
{
	char	**cmds;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(cmd, '|');
	cmds = malloc(sizeof(char *) * tab_len(tmp) + 1);
	while (tmp[i] != NULL)
	{
		cmds[i] = ft_strtrim(tmp[i], " ");
		i++;
	}
	cmds[i] = NULL;
	tabfree(tmp);
	return (cmds);
}

char	**clean_quotes(char **cmds, t_parse p)
{
	char	**new;
	char	**token;
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (p.double_q == 0 && p.single_q == 0)
		return (cmds);
	new = malloc(sizeof(char *) * tab_len(cmds) + 1);
	while (cmds[j] != NULL)
	{
		i = 0;
		tmp = tokenize(cmds[j]);
		token = malloc(sizeof(char *) * tab_len(tmp) + 1);
		while (tmp[i] != NULL)
		{
			token[i] = ft_strtrim(tmp[i], "\"");
			i++;
		}
		token[i] = NULL;
		new[j] = tab_to_str(token);
		j++;
	}
	return (cmds);
}

char	**clean_quotes_token(char **token, t_parse p)
{
	char	**new;
	int		i;

	i = 0;
	if (p.double_q == 0 && p.single_q == 0)
		return (token);
	new = malloc(sizeof(char *) * tab_len(token) + 1);
	while (token[i] != NULL)
	{
		if (*token[i] == '\0')
			new[i] = ft_strdup(" ");
		else
			new[i] = ft_strtrim(token[i], "\"");
		i++;
	}
	new[i] = NULL;
	return (new);
}

int check_closed_quotes(t_tprint tp)
{
	int i;

	i = 1;
	while (i <= tp.print[0])
	{
		if(tp.print[i] == -1)
		{
			printf(ERROR_QUOTES);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor(char *cmd, t_tab *t)
{
	t_parse		p;
	t_tprint	tp;
	
	tp = parsing_master(cmd);
	if (check_closed_quotes(tp))
		return (1);
	display_tab_and_int(tp.print, tp.tab);
	p = stock_parsing_infos(tp);
	// p = stock_parsing_infos(cmd);
	t->p = p;
	if (pre_parsing_errors(cmd, p))
		return (1);
	p.cmds = clean_spaces(cmd);

	// if (tab_len(p.cmds) == 1 && p.redir == 0)
	// {
		// if (launch_cmds(p.cmds[0], t))
		// 	other_with_fork(p.cmds[0], t);
	// }
	// else if (p.pipes > 0 && p.redir == 0)
	// 	launch_with_pipes(p, t);
	// else if (p.redir > 0)
	// 	launch_with_redir(p, t);
	return (0);
}

int	launch_cmds(char *cmd, t_tab *t)
{
	char	**token;
	// char	**cleaned;
	t_tprint tp;

	token = tokenize(cmd);
	if (!ft_strncmp(cmd, "exit", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		ft_exit(cmd, t);
	else if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		t = ms_b_cd(cmd, t);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
	{
		tp = parsing_master(cmd);
		echo(tp, *t);
	}
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		t = ft_export(t, token);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		t = unset_var(t, token);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		display_env(t->env);
	else
		return (1);
	return (0);
}

int	is_a_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (1);
	else
		return (0);
}

int	launch_builtins_with_redir(char *cmd, t_tab *t, int fd, int std)
{
	char	**token;

	token = tokenize(cmd);
	dup2(fd, std);
	if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		t = ms_b_cd(cmd, t);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		printf("En construction\n");
		// echo(token, *t);
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		t = ft_export(t, token);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		t = unset_var(t, token);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		display_env(t->env);
	else
		return (1);
		// test_other(cmd, t, fd, std);
		// ms_b_other(cmd);
	return (0);
}

int	launch_builtins_with_doors(char *cmd, t_tab *t, t_doors doors)
{
	char	**token;

	token = tokenize(cmd);
	dup2(doors.in, STDIN_FILENO);
	dup2(doors.out, STDOUT_FILENO);
	if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		t = ms_b_cd(cmd, t);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		printf("En construction\n");
		// echo(token, *t);
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		t = ft_export(t, token);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		t = unset_var(t, token);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		display_env(t->env);
	else
		return (1);
		// test_other(cmd, t, fd, std);
		// ms_b_other(cmd);
	return (0);
}
