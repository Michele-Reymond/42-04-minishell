/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:58:02 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/30 20:38:59 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_parent_in_doors(pid_t pid, char *cmd, t_tprint tp, t_tab *t)
{
	int			status;

	waitpid(pid, &status, 0);
	if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		t = ms_b_cd(tp, t);
	else if (!ft_strncmp(cmd, "export", 6)
		&& (cmd[6] == ' ' || cmd[6] == '\0'))
		t = ft_export(t, tp);
	else if (!ft_strncmp(cmd, "unset", 5)
		&& (cmd[5] == ' ' || cmd[5] == '\0'))
		t = unset_var(t, tp.tab);
	free(cmd);
	free_tp(tp);
	tabfree(t->p.cmds);
}

void	fork_and_launch_builtin_doors(char *cmd, t_tab *t, t_doors doors)
{
	pid_t		pid;
	t_tprint	tp;

	tp = parsing_master(cmd);
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
	{
		free_tp(tp);
		launch_builtins_with_doors(cmd, t, doors);
		free(cmd);
		close(doors.in);
		close(doors.out);
		exit (0);
	}
	else
		launch_parent_in_doors(pid, cmd, tp, t);
}

t_doors	set_doors_in_pipes(char **cmds, t_redir *r)
{
	t_doors	doors;
	int		i;

	i = 0;
	doors = init_doors();
	while (cmds[i] != NULL)
	{
		doors = set_redir_in_pipe(r[i], doors);
		i++;
	}
	return (doors);
}

// this function is used in pipes with redir function
void	launching_redirs(char *cmd, t_tab *t)
{
	t_redir	*r;
	char	**newcmds;

	if (nbr_of_redir(cmd) == 0)
	{
		if (launch_cmds(cmd, t))
			other_basic(cmd, t);
	}
	else if (nbr_of_redir(cmd) == 1)
		launching_multiredirs(cmd, t);
	else if (nbr_of_redir(cmd) > 1)
	{
		newcmds = a_redir_pro_cmd(cmd);
		r = stock_redir_infos(newcmds);
		launch_multiple_redir_in_pipes(r, t, newcmds);
	}
}

// launch cmds with redirections symbol
// this function is used in monitor
void	launch_with_redir(t_parse p, t_tab *t)
{
	t_redir	*r;
	t_redir	redir;
	char	**newcmds;
	int		len;

	if (tab_len(p.cmds) == 1 && p.redir <= 1)
	{
		r = stock_redir_infos(p.cmds);
		len = tab_len(p.cmds);
		tabfree(p.cmds);
		p.cmds = rebuilt_cmds(r, len);
		t->p.cmds = p.cmds;
		redir = dup_redir(r[0]);
		free_all_t_redirs(r, len);
		launch_redir(redir, t, p.cmds[0]);
	}
	else if (p.pipes == 0 && p.redir > 1)
	{
		newcmds = a_redir_pro_cmd(p.cmds[0]);
		r = stock_redir_infos(newcmds);
		len = tab_len(newcmds);
		launch_multiple_redir(r, t, newcmds);
	}
	else
		launch_pipes_with_redir(p, t);
}
