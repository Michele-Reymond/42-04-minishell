/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 11:16:52 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_one_redir(t_parse p, t_tab *t)
{
	t_redir	*r;
	int		len;
	t_redir	redir;

	r = stock_redir_infos(p.cmds);
	if (stock_is_ok(r, p.cmds))
		return ;
	len = tab_len(p.cmds);
	tabfree(p.cmds);
	p.cmds = rebuilt_cmds(r, len);
	t->p.cmds = p.cmds;
	redir = dup_redir(r[0]);
	free_all_t_redirs(r, len);
	launch_redir(redir, t, p.cmds[0]);
}

int	stock_is_ok(t_redir	*redir, char **tab)
{
	if (redir == NULL)
	{
		tabfree(tab);
		return (1);
	}
	return (0);
}

void	launch_child_in_set(t_redir r, int tmpfile)
{
	char	*input;

	signal(SIGINT, signal_heredoc_child);
	input = readline("> ");
	while (input != NULL)
	{
		if (strlen(input) > 0)
		{
			if (!ft_strncmp(input, r.dest, ft_strlen(r.dest)))
				break ;
			write(tmpfile, input, ft_strlen(input));
			write(tmpfile, "\n", 1);
		}
		free(input);
		input = readline("> ");
	}
	exit(0);
}

t_doors	set_redir_in_pipe(t_redir r, t_doors doors)
{
	t_doors	new;

	if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		new = set_out(r, doors);
	else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		new = set_in(r, doors);
	else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		new = set_out_d(r, doors);
	else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		new = set_in_d_in_pipe(doors);
	else
		new = doors;
	return (new);
}

t_doors	set_redirection(t_redir r, t_doors doors)
{
	t_doors	new;

	if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		new = set_out_p(r, doors);
	else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		new = set_in_p(r, doors);
	else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		new = set_out_d_p(r, doors);
	else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		new = set_in_d_p(r, doors);
	else
		new = doors;
	return (new);
}
