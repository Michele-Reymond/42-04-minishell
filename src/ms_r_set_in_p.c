/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_set_in_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 12:51:44 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// >
t_doors	set_out_p(t_redir r, t_doors doors)
{
	int		outfile;
	t_doors	new;

	new.in = -1;
	new.out = -1;
	if (check_files_out_in_p(r.dest))
		return (new);
	outfile = open(r.dest, O_TRUNC | O_WRONLY);
	free_t_redirs(r);
	if (outfile < 0)
	{
		new.in = -1;
		new.out = -1;
	}
	else
	{
		new.in = doors.in;
		new.out = outfile;
	}
	return (new);
}

// <
t_doors	set_in_p(t_redir r, t_doors doors)
{
	int		infile;
	t_doors	new;

	new.in = -1;
	new.out = -1;
	if (check_files_in_p(r.dest))
		return (new);
	infile = open(r.dest, O_RDONLY);
	free_t_redirs(r);
	if (infile < 0)
	{
		new.in = -1;
		new.out = -1;
	}
	else
	{
		new.in = infile;
		new.out = doors.out;
	}
	return (new);
}

// <<
t_doors	set_in_d_p(t_redir r, t_doors doors)
{
	int		tmpfile;
	pid_t	pid;
	int		status;
	t_doors	new;

	new.in = -1;
	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		return (new);
	}
	new.in = tmpfile;
	new.out = doors.out;
	pid = fork();
	pid_errors(pid);
	if (pid == 0)
		launch_child_in_set(r, tmpfile);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_heredoc_parent);
	}
	return (new);
}

// >>
t_doors	set_out_d_p(t_redir r, t_doors doors)
{
	int		outfile;
	t_doors	new;

	new.in = -1;
	new.out = -1;
	if (check_files_out_in_p(r.dest))
		return (new);
	outfile = open(r.dest, O_WRONLY | O_APPEND);
	free_t_redirs(r);
	if (outfile < 0)
	{
		new.in = -1;
		new.out = -1;
	}
	else
	{
		new.in = doors.in;
		new.out = outfile;
	}
	return (new);
}
