/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_launch_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 13:01:41 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// >
void	launch_out_p(t_redir r, t_tab *t, char *cmd)
{
	int		outfile;

	if (check_files_out_in_p(r.dest))
		return ;
	outfile = open(r.dest, O_TRUNC | O_WRONLY);
	free_t_redirs(r);
	if (outfile < 0)
		return ;
	if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, outfile, STDOUT_FILENO);
	else
		other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// >>
void	launch_out_d_p(t_redir r, t_tab *t, char *cmd)
{
	int		outfile;

	if (check_files_out_in_p(r.dest))
		return ;
	outfile = open(r.dest, O_WRONLY | O_APPEND);
	free_t_redirs(r);
	if (outfile < 0)
		return ;
	if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, outfile, STDOUT_FILENO);
	else
		other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// <
void	launch_in_basic(t_redir r, t_tab *t, char *cmd)
{
	int		infile;

	if (check_files_in_basic(r.dest))
		return ;
	infile = open(r.dest, O_RDONLY);
	free_t_redirs(r);
	if (infile < 0)
		return ;
	if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, infile, STDIN_FILENO);
	else
		other_redir_and_fork(cmd, t, infile, STDIN_FILENO);
}

// <<
void	launch_in_d_p(t_redir r, t_tab *t, char *cmd)
{
	int		tmpfile;
	pid_t	pid;

	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		tabfree(t->p.cmds);
		perror("minishell: ");
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		close(tmpfile);
		tabfree(t->p.cmds);
		return (perror("Fork: "));
	}
	if (pid == 0)
		launch_child_heredoc(cmd, r, tmpfile, t);
	else
	{
		signal(SIGINT, SIG_IGN);
		launch_parent_heredoc(r, t, pid, tmpfile);
		signal(SIGINT, signal_heredoc_parent);
	}
}
