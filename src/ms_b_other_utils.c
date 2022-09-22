/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/09/22 12:59:32 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_neg(char **paths, char *first_cmd, char **envp, char **flags)
{
	char	**new_flags;
	int		ret;

	ret = execve(first_cmd, flags, envp);
	if (ret < 0 && ft_strrchr(flags[0], '/'))
	{
		new_flags = add_to_tab_begin(flags, "/usr/bin/env");
		ret = execve("/usr/bin/env", new_flags, envp);
		tabfree(new_flags);
	}
	if (ret < 0)
	{
		printf("minishell: %s: ", first_cmd);
		printf(ERROR_CMD_NOT_FOUND);
		ft_free(first_cmd);
		tabfree(paths);
		exit(errno);
	}
}

void	exec_cmd(char **paths, char *first_cmd, char **envp, char **flags)
{
	int		i;
	char	*cmd;
	char	*tmp;
	int		ret;

	i = -1;
	while (paths[++i] != NULL)
	{	
		tmp = ft_strjoin("/", first_cmd);
		cmd = ft_strjoin(paths[i], tmp);
		ret = execve(cmd, flags, envp);
		ft_free(cmd);
		ft_free(tmp);
	}
	if (ret < 0)
		exec_neg(paths, first_cmd, envp, flags);
	ft_free(first_cmd);
}

void	launch_child_process(char *buff, char **paths, char **envp)
{
	char		*first_cmd;
	t_tprint	tp;

	tp = parsing_master(buff);
	first_cmd = ft_strdup(tp.tab[0]);
	exec_cmd(paths, first_cmd, envp, tp.tab);
	free_tp(tp);
	ft_free(first_cmd);
}

void	status_of_child(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 2)
			g_exit_status = 127;
		else
			g_exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		g_exit_status = SIGINT;
		if (g_exit_status != 131)
			g_exit_status += 128;
	}
}

char	**pathextraction(char **env)
{
	char	*currentpath;
	char	**paths;

	currentpath = ft_getenv(env);
	currentpath = ft_strjoin(currentpath, ":");
	currentpath = ft_strjoin(currentpath, getcwd (NULL, 0));
	paths = ft_split(currentpath, ':');
	free (currentpath);
	return (paths);
}
