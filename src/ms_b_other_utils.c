/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/09/20 17:21:15 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env)
{
	int		pos;
	char	**tmp;
	char	*path;

	pos = var_exist(env, "PATH");
	if (!ft_strncmp(env[pos], "PATH", 4) && (env[pos][4] == '='))
	{
		tmp = ft_split(env[pos], '=');
		path = ft_strdup(tmp[1]);
		tabfree(tmp);
	}
	else
		path = ft_strdup("");
	return (path);
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
		// printf("%s\n", cmd);
		ret = execve(cmd, flags, envp);
		ft_free(cmd);
		ft_free(tmp);
	}
	if (ret < 0)
	{
		cmd = first_cmd;
		// printf("%s\n", cmd);
		// display_tab(flags);
		ret = execve(cmd, flags, envp);
	}
	if (ret < 0)
	{
		printf("minishell: %s: ", first_cmd);
		printf(ERROR_CMD_NOT_FOUND);
		ft_free(first_cmd);
		tabfree(paths);
		exit(errno);
	}
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
