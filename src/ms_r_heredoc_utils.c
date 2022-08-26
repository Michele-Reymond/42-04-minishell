/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:32:35 by mreymond         ###   ########.fr       */
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
	while (newcmds[i] != NULL)
	{
		if (!ft_strncmp(r[i].redir, "<<", 2))
			break ;
		i++;
	}
	launch_heredoc(r[i].dest);
}

int is_heredoc(char *cmd)
{
	int		*nbr;
	int		ret;

	nbr = check_redir(cmd, '<');
	ret = nbr[1];
	free(nbr);
	return (ret);
}
