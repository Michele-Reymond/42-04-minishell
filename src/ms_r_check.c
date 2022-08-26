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

int nbr_of_redir(char *cmd)
{
	int		*nbr1;
	int		*nbr2;
	int		total;

	nbr1 = check_redir(cmd, '>');
	nbr2 = check_redir(cmd, '<');
	total = nbr1[0] + nbr1[1] + nbr2[0] + nbr2[1];
	free(nbr1);
	free(nbr2);
	return (total);
}

void    which_redir(t_redir *r, char *cmd)
{
	int		*nbr1;
	int		*nbr2;

	nbr1 = check_redir(cmd, '>');
	nbr2 = check_redir(cmd, '<');
	if (nbr2[0] > 0)
		r->redir = ft_strdup("<");
	else if (nbr2[1] > 0)
		r->redir = ft_strdup("<<");
	else if (nbr1[0] > 0 )
		r->redir = ft_strdup(">");
	else if (nbr1[1] > 0)
		r->redir = ft_strdup(">>");
	else
		r->redir = ft_strdup("");
}