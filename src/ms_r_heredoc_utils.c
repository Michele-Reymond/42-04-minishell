/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 15:16:59 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(char *cmd)
{
	char	**newcmds;
	t_redir	*r;
	int		i;

	i = 0;
	newcmds = a_redir_pro_cmd(cmd);
	r = stock_redir_infos(newcmds);
	if (stock_is_ok(r, newcmds))
		return ;
	while (newcmds[i] != NULL)
	{
		if (!ft_strncmp(r[i].redir, "<<", 2))
			break ;
		i++;
	}
	launch_heredoc(r[i].dest);
}

int	is_heredoc(char *cmd)
{
	int		*nbr;
	int		ret;

	nbr = check_redir(cmd, '<');
	ret = nbr[1];
	free(nbr);
	return (ret);
}

void	launch_parent_heredoc(t_redir r, t_tab *t, pid_t pid, int tmpfile)
{
	int		status;

	waitpid(pid, &status, 0);
	close(tmpfile);
	tabfree(t->p.cmds);
	free_t_redirs(r);
	unlink(".heredoc");
}

int	write_heredoc(char	*input, t_redir r, int tmpfile)
{
	if (strlen(input) > 0)
	{
		if (!ft_strncmp(input, r.dest, ft_strlen(r.dest)))
			return (1);
		write(tmpfile, input, ft_strlen(input));
		write(tmpfile, "\n", 1);
	}
	return (0);
}
