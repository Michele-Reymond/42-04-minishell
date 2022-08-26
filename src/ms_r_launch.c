/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/09 11:08:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// >
void launch_out(t_redir r, t_tab *t, char *cmd)
{
	int		outfile;

	check_files_out(r.dest);
	outfile = open(r.dest, O_TRUNC | O_WRONLY);
	free_t_redirs(r);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, outfile, STDOUT_FILENO);
	else
		other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// >>
void launch_out_d(t_redir r, t_tab *t, char *cmd)
{
	int		outfile;

	check_files_out(r.dest);
	outfile = open(r.dest, O_WRONLY | O_APPEND);
	free_t_redirs(r);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, outfile, STDOUT_FILENO);
	else
		other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// <
void launch_in(t_redir r, t_tab *t, char *cmd)
{
	int		infile;

	check_files_in(r.dest);
	infile = open(r.dest, O_RDONLY);
	free_t_redirs(r);
	if (infile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
   if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, infile, STDIN_FILENO);
	else
		other_redir_and_fork(cmd, t, infile, STDIN_FILENO);
}

// <
void launch_in_basic(t_redir r, t_tab *t, char *cmd)
{
	int		infile;
	
	if (check_files_in_basic(r.dest))
		return ;
	infile = open(r.dest, O_RDONLY);
	free_t_redirs(r);
	if (infile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	if (is_a_builtin(cmd))
		fork_and_launch_builtin(cmd, t, infile, STDIN_FILENO);
	else    
		other_redir_and_fork(cmd, t, infile, STDIN_FILENO);
}
