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

void	exec_cmd(char **paths, char *first_cmd, char **envp, char **flags)
{
	int		i;
	char	*cmd;
	int		ret;

	i = 0;
	while (paths[i] != NULL)
	{
		cmd = ft_strjoin(paths[i], first_cmd);
		ret = execve(cmd, flags, envp);
		ft_free(cmd);
		i++;
	}
	if (ret < 0)
	{
		cmd = first_cmd;
		ret = execve(cmd, flags, envp);
	}
	if (ret < 0)
	{
		printf("minishell: %s: ", &first_cmd[1]);
		printf(ERROR_CMD_NOT_FOUND);
		ft_free(first_cmd);
		tabfree(paths);
		exit(errno);
	}
	ft_free(first_cmd);
}

void	launch_child_process(char *buff, char **paths, char **envp)
{
	char	*first_cmd;
	t_tprint	tp;

	tp = parsing_master(buff);
	first_cmd = ft_strjoin("/", tp.tab[0]);
	exec_cmd(paths, first_cmd, envp, tp.tab);
	free_tp(tp);
	ft_free(first_cmd);
}

void	status_of_child(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 2)
			exit_status = 127;
		else
			exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		exit_status = SIGINT;
		if (exit_status != 131)
			exit_status += 128;
	}
}
