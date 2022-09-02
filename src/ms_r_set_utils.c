/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_set_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:40:53 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// >
t_doors	set_out(t_redir r, t_doors doors)
{
	int		outfile;
	t_doors	new;

	check_files_out(r.dest);
	outfile = open(r.dest, O_TRUNC | O_WRONLY);
	free_t_redirs(r);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	new.in = doors.in;
	new.out = outfile;
	return (new);
}

// >>
t_doors	set_out_d(t_redir r, t_doors doors)
{
	int		outfile;
	t_doors	new;

	check_files_out(r.dest);
	outfile = open(r.dest, O_WRONLY | O_APPEND);
	free_t_redirs(r);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	new.in = doors.in;
	new.out = outfile;
	return (new);
}

// <
t_doors	set_in(t_redir r, t_doors doors)
{
	int		infile;
	t_doors	new;

	check_files_in(r.dest);
	infile = open(r.dest, O_RDONLY);
	free_t_redirs(r);
	if (infile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	new.in = infile;
	new.out = doors.out;
	return (new);
}

// <<
t_doors	set_in_d(t_redir r, t_doors doors)
{
	int		tmpfile;
	pid_t	pid;
	int		status;
	t_doors	new;

	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	pid_errors(pid);
	if (pid == 0)
	{
		launch_child_in_set(r, tmpfile);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		new.in = tmpfile;
		new.out = doors.out;
		return (new);
	}
}

t_doors	set_in_d_in_pipe(t_doors doors)
{
	int		tmpfile;
	t_doors	new;

	tmpfile = open(".heredoc", O_RDONLY);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	new.in = tmpfile;
	new.out = doors.out;
	return (new);
}
