/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_set_in_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 16:02:16 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**rebuilt_cmds(t_redir *r, int len)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		cmds[i] = ft_strdup(r[i].cmd);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

static int	check_files_in_p(char *file)
{
	if (access(file, F_OK) != 0)
	{
		printf("minishell: %s : %s \n", file, strerror(errno));
		g_exit_status = 1;
		return (1);
	}
	if (access(file, R_OK) != 0)
	{
		printf("minishell: %s : %s \n", file, strerror(errno));
		g_exit_status = 1;
		return (1);
	}
	return (0);
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
