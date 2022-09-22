/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 13:56:31 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_child_in_set(t_redir r, int tmpfile)
{
	char	*input;

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
		new = set_out(r, doors);
	else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		new = set_in_p(r, doors);
	else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		new = set_out_d(r, doors);
	else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		new = set_in_d(r, doors);
	else
		new = doors;
	return (new);
}
