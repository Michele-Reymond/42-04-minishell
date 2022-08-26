/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:15:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:28:08 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(int **fd, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (pipe(fd[i]) == -1)
			return ;
		i++;
	}
}

void	check_files_needs(char *cmd)
{
	t_redir	*r;
	char	**tmp;
	char	**newcmds;

	if (is_heredoc(cmd))
		read_heredoc(cmd);
	tmp = new_tab();
	newcmds = add_to_tab(tmp, cmd);
	tabfree(tmp);
	r = stock_redir_infos(newcmds);
	if (r[0].redir[0] == '<' && ft_strlen(r[0].redir) == 1)
	{
		if (access(r[0].dest, F_OK) != 0)
			printf("minishell: %s : %s \n", r[0].dest,  strerror(errno));
		else if (access(r[0].dest, R_OK) != 0)
			printf("minishell: %s : %s \n", r[0].dest,  strerror(errno));
	}
	free_all_t_redirs(r, tab_len(newcmds));
	tabfree(newcmds);
}

// lancer les processus enfants
void	child_process(int **fd, int pos, int nbr)
{
	closing_loop_in(fd, pos, nbr);
	if (pos == 0)
		dup2(fd[pos][1], STDOUT_FILENO);
	else if (pos != 0 && !(pos == nbr))
	{
		dup2(fd[pos - 1][0], STDIN_FILENO);
		dup2(fd[pos][1], STDOUT_FILENO);
	}
	else
		dup2(fd[pos - 1][0], STDIN_FILENO);
}

void	launching_pipes_in_child(t_parse p, t_tab *t, pid_t *pid, int **fd)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (i < p.nbr_cmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return ;
		if (pid[i] == 0)
		{
			child_process(fd, i, p.pipes);
			if (launch_cmds(p.cmds[i], t))
				other_basic(p.cmds[i], t);
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

void	launching_pipes_in_parent(t_parse p, pid_t *pid, int **fd)
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
