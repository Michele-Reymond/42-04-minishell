/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:15:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 10:38:31 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_with_pipes(t_parse p, t_tab *t)
{
	pid_t	*pid;
	int		**fd;
	int		i;

	i = -1;
	pid = malloc(sizeof(pid_t) * p.nbr_cmd);
	fd = malloc(sizeof(int *) * p.pipes);
	while (i++ < p.pipes - 1)
		fd[i] = malloc(sizeof(int) * 2);
	create_pipes(fd, p.pipes);
	launching_pipes_in_child(p, t, pid, fd);
	launching_pipes_in_parent(p, pid, fd);
	tabfree(t->p.cmds);
}

void	launching_redirs_in_child(t_parse p, t_tab *t, pid_t *pid, int **fd)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (i < p.nbr_cmd)
	{
		check_files_needs(p.cmds[i]);
		pid[i] = fork();
		if (pid[i] < 0)
			return ;
		if (pid[i] == 0)
		{
			child_process(fd, i, p.pipes);
			launching_redirs(p.cmds[i], t);
			closing_loop_out(fd, i, p.pipes);
			while (k++ < p.pipes - 1)
				free(fd[k]);
			free(fd);
			free(pid);
			exit (0);
		}
		i++;
	}
}

void	launching_redirs_in_parent(t_parse p, pid_t *pid, int **fd)
{
	int		i;
	int		status;

	if (pid != 0)
	{
		parent_closing_loop(fd, p.pipes);
		i = 0;
		while (i < p.nbr_cmd)
		{
			waitpid(pid[i], &status, 0);
			i++;
		}
		if (access(".heredoc", F_OK) == 0)
			unlink(".heredoc");
		i = 0;
		while (i < p.pipes)
		{
			free(fd[i]);
			i++;
		}
		free(fd);
		free(pid);
	}
}

///pipes & redirections
void	launch_pipes_with_redir(t_parse p, t_tab *t)
{
	pid_t	*pid;
	int		**fd;
	int		i;

	i = -1;
	pid = malloc(sizeof(pid_t) * p.nbr_cmd);
	fd = malloc(sizeof(int *) * p.pipes);
	while (i++ < p.pipes - 1)
		fd[i] = malloc(sizeof(int) * 2);
	create_pipes(fd, p.pipes);
	launching_redirs_in_child(p, t, pid, fd);
	launching_redirs_in_parent(p, pid, fd);
	tabfree(t->p.cmds);
}
