/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:15:10 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	monitor(char *cmd, t_tab *t)
{
	t_parse		p;
	t_tprint	tp;

	tp = parsing_master(cmd);
	ft_free(cmd);
	if (check_closed_quotes(tp))
		return (free_tp_status_error(tp));
	p = stock_parsing_infos(tp);
	if (!(p.redir_in >= 0 && p.redir_out >= 0))
		return (free_tp_status_error(tp));
	p.cmds = split_pipes(tp, p.pipes);
	if (p.cmds == NULL)
		return (free_tp_status_error(tp));
	t->p = p;
	free_tp(tp);
	if (tab_len(p.cmds) == 1 && p.redir == 0)
	{
		if (launch_cmds(p.cmds[0], t))
			other_with_fork(p.cmds[0], t);
	}
	else if (p.pipes > 0 && p.redir == 0)
		launch_with_pipes(p, t);
	else if (p.redir > 0)
		launch_with_redir(p, t);
	return (0);
}

int	launch_cmds(char *cmd, t_tab *t)
{
	t_tprint	tp;

	tp = parsing_master(cmd);
	if (!ft_strncmp(cmd, "exit", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		ft_exit(cmd, t);
	else if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		t = ms_b_cd(tp, t);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		echo(tp, *t);
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		t = ft_export(t, tp);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		t = unset(t, tp);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		display_env(t->env);
	else
	{
		free_tp(tp);
		return (1);
	}
	free_tp(tp);
	tabfree(t->p.cmds);
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
	int	ret;

	dup2(fd, std);
	ret = launch_cmds(cmd, t);
	return (ret);
}

int	launch_builtins_with_doors(char *cmd, t_tab *t, t_doors doors)
{
	int	ret;

	dup2(doors.in, STDIN_FILENO);
	dup2(doors.out, STDOUT_FILENO);
	ret = launch_cmds(cmd, t);
	return (ret);
}
