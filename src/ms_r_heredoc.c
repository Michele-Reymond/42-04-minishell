/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 17:31:46 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_heredoc_with_stop(int tmpfile, char *stop)
{
	char	*input;

	signal(SIGINT, signal_heredoc_child);
	input = readline("> ");
	while (input != NULL)
	{
		if (strlen(input) > 0)
		{
			if (!ft_strncmp(input, stop, ft_strlen(stop)))
				break ;
			write(tmpfile, input, ft_strlen(input));
			write(tmpfile, "\n", 1);
		}
		free(input);
		input = readline("> ");
	}
	close(tmpfile);
	exit(0);
}

// <<
void	launch_heredoc(char *stop)
{
	int		tmpfile;
	pid_t	pid;
	int		status;

	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	pid_errors(pid);
	if (pid == 0)
		launch_heredoc_with_stop(tmpfile, stop);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		close(tmpfile);
		signal(SIGINT, signal_heredoc_parent);
	}
}

// <<
void	launch_in_d_in_pipe(t_tab *t, char *cmd)
{
	char	*newcmd;

	newcmd = ft_strjoin(cmd, " .heredoc");
	if (launch_cmds(newcmd, t))
		other_basic(newcmd, t);
	free(newcmd);
}

void	launch_child_heredoc(char *cmd, t_redir r, int tmpfile, t_tab *t)
{
	char	*input;
	char	*newcmd;
	int		fd;

	signal(SIGINT, signal_heredoc_child);
	input = readline("> ");
	while (input != NULL)
	{
		if (write_heredoc(input, r, tmpfile))
			break ;
		free(input);
		input = readline("> ");
	}
	free_t_redirs(r);
	newcmd = ft_strdup(cmd);
	fd = open(".heredoc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	if (launch_cmds(newcmd, t))
		other_basic(newcmd, t);
	free(newcmd);
	tabfree(t->p.cmds);
	close(tmpfile);
	exit(0);
}

// <<
void	launch_in_d(t_redir r, t_tab *t, char *cmd)
{
	int		tmpfile;
	pid_t	pid;

	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		tabfree(t->p.cmds);
		perror("minishell: ");
		exit(EXIT_FAILURE);
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
