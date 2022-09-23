/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_set_in_p_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/23 11:25:18 by mreymond         ###   ########.fr       */
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

int	check_files_in_p(char *file)
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

int	check_files_out_in_p(char *file)
{
	if (access(file, F_OK) != 0)
		open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(file, W_OK) != 0)
	{
		printf("minishell: %s : %s \n", file, strerror(errno));
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
