/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/08/10 12:08:11 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// lancer cette comande dans les pipes
void other_basic(char *buf, t_tab *t)
{
	char	**paths;
	
	paths = ft_split(getenv("PATH"), ':');
	launch_child_process(buf, paths, t->env);
	tabfree(paths);
}

// lancer cette comande si commande seule sans redirections
void other_with_fork(char *buf, t_tab *t)
{
	char	**paths;
	pid_t	pid;
	int		status;

	paths = ft_split(getenv("PATH"), ':');
	pid = fork();
	if (pid < 0)
	{
		tabfree(t->p.cmds);
		tabfree(paths);
		return (perror("Fork: "));
	}
	if (pid == 0)
	{
		launch_child_process(buf, paths, t->env);
		tabfree(t->p.cmds);
		tabfree(paths);
		exit (0);
	}
	else {
		waitpid(pid, &status, 0);
		status_of_child(status);
		tabfree(t->p.cmds);
		tabfree(paths);
	}
}

// lancer cette comande si commande seule avec redirections
void other_redir_and_fork(char *buf, t_tab *t, int fd, int std)
{
	char	**paths;
	pid_t	pid;
	int		status;

	paths = ft_split(getenv("PATH"), ':');
	pid = fork();
	if (pid < 0)
	{
		tabfree(t->p.cmds);
		tabfree(paths);
		return (perror("Fork: "));
	}
	if (pid == 0)
	{
		dup2(fd, std);
		launch_child_process(buf, paths, t->env);
		tabfree(paths);
		tabfree(t->p.cmds);
		exit (0);
	}
	else 
	{
		waitpid(pid, &status, 0);
		status_of_child(status);
		tabfree(t->p.cmds);
		tabfree(paths);
	}
}

// lancer cette comande si commande seule avec redirections
void other_doors_and_fork(char *buf, t_tab *t, t_doors doors)
{
	char	**paths;
	pid_t	pid;
	int		status;

	paths = ft_split(getenv("PATH"), ':');
	pid = fork();
	if (pid < 0)
	{
		tabfree(t->p.cmds);
		tabfree(paths);
		return (perror("Fork: "));
	}
	if (pid == 0)
	{
		dup2(doors.in, STDIN_FILENO);
		dup2(doors.out, STDOUT_FILENO);
		launch_child_process(buf, paths, t->env);
		tabfree(t->p.cmds);
		tabfree(paths);
	}
	else {
		waitpid(pid, &status, 0);
		status_of_child(status);
		tabfree(t->p.cmds);
		tabfree(paths);
	}
}
