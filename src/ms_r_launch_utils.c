/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_launch_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 16:37:50 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_b_child(char *cmd, t_tab *t, int fd, int std)
{
	dup2(fd, std);
	launch_cmds(cmd, t);
	if (t->env != NULL)
		tabfree(t->env);
	if (t->exp != NULL)
		tabfree(t->exp);
	close(fd);
	exit (0);
}

void	fork_and_launch_builtin(char *cmd, t_tab *t, int fd, int std)
{
	pid_t		pid;
	int			status;
	t_tprint	tp;

	tp = parsing_master(cmd);
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
	{
		free_tp(tp);
		launch_b_child(cmd, t, fd, std);
	}
	else
	{
		close(fd);
		waitpid(pid, &status, 0);
		if (!ft_strncmp(cmd, "cd", 2)
			&& (cmd[2] == ' ' || cmd[2] == '\0'))
			t = ms_b_cd(tp, t);
		else if (!ft_strncmp(cmd, "export", 6)
			&& (cmd[6] == ' ' || cmd[6] == '\0'))
			t = ft_export(t, tp);
		else if (!ft_strncmp(cmd, "unset", 5)
			&& (cmd[5] == ' ' || cmd[5] == '\0'))
			t = unset_var(t, tp.tab);
		free_tp(tp);
		tabfree(t->p.cmds);
	}
}

void	pid_errors(pid_t pid)
{
	if (pid < 0)
	{
		perror("minishell: Fork: ");
		exit(EXIT_FAILURE);
	}
}

void	launch_redir_in_pipe(t_redir r, t_tab *t, char *cmd)
{
	if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		launch_out(r, t, cmd);
	else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		launch_in(r, t, cmd);
	else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		launch_out_d(r, t, cmd);
	else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		launch_in_d_in_pipe(t, cmd);
}

void	launch_redir(t_redir r, t_tab *t, char *cmd)
{
	if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		launch_out(r, t, cmd);
	else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		launch_in_basic(r, t, cmd);
	else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		launch_out_d(r, t, cmd);
	else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		launch_in_d(r, t, cmd);
}
