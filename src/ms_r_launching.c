/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_launching.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/21 11:23:07 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_doors	make_doors(char **cmds, t_redir *r)
{
	t_doors		doors;
	int			i;

	i = 0;
	doors = init_doors();
	while (cmds[i] != NULL)
	{
		doors = set_redirection(r[i], doors);
		i++;
	}
	return (doors);
}

void	launch_multiple_redir(t_redir *r, t_tab *t, char **cmds)
{
	t_doors		doors;
	char		*newcmd;
	char		*cmd;

	doors = make_doors(cmds, r);
	cmd = ft_strdup(r[0].cmd);
	free(r);
	tabfree(cmds);
	if (access(".heredoc", F_OK) == 0 && *cmd != '\0')
	{
		newcmd = ft_strjoin(cmd, " .heredoc");
		free(cmd);
		cmd = newcmd;
	}
	if (is_a_builtin(cmd))
		fork_and_launch_builtin_doors(cmd, t, doors);
	else
		other_doors_and_fork(cmd, t, doors);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
}

void	launching_multiredirs(char *cmd, t_tab *t)
{
	t_redir	*r;
	t_redir	redir;
	char	**newcmds;
	char	**tmp;
	int		len;

	tmp = new_tab();
	newcmds = add_to_tab(tmp, cmd);
	tabfree(tmp);
	r = stock_redir_infos(newcmds);
	len = tab_len(newcmds);
	tabfree(newcmds);
	newcmds = rebuilt_cmds(r, len);
	redir = dup_redir(r[0]);
	free_all_t_redirs(r, len);
	launch_redir_in_pipe(redir, t, newcmds[0]);
	tabfree(newcmds);
}

void	launch_multiple_redir_in_pipes(t_redir *r, t_tab *t, char **cmds)
{
	t_doors	doors;
	char	*newcmd;

	doors = set_doors_in_pipes(cmds, r);
	if (access(".heredoc", F_OK) == 0 && *(r[0].cmd) != '\0')
	{
		newcmd = ft_strjoin(r[0].cmd, " .heredoc");
		free(r[0].cmd);
		r[0].cmd = newcmd;
	}
	if (is_a_builtin(r[0].cmd))
		launch_builtins_with_doors(r[0].cmd, t, doors);
	else
		other_doors_and_fork(r[0].cmd, t, doors);
	free_all_t_redirs(r, tab_len(cmds) - 1);
	tabfree(cmds);
	close(doors.in);
	close(doors.out);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
}

void	pid_errors(pid_t pid)
{
	if (pid < 0)
	{
		perror("minishell: Fork: ");
		exit(EXIT_FAILURE);
	}
}
