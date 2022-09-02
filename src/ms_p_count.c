/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:16:39 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_tprint tp)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
			nbr += how_many_in_str(tp.tab[i], '|');
		i++;
	}
	return (nbr);
}

int	count_doubles(t_tprint tp)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 1 || tp.print[i + 1] == 4)
			nbr++;
		i++;
	}
	return (nbr);
}

int	count_singles(t_tprint tp)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 0 || tp.print[i + 1] == 3)
			nbr++;
		i++;
	}
	return (nbr);
}

int	count_dollar(t_tprint tp)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] != 0 && tp.print[i + 1] != 3)
			nbr += how_many_in_str(tp.tab[i], '$');
		i++;
	}
	return (nbr);
}

void	count_redir(t_tprint tp, t_parse *p)
{
	int		i;
	int		*nbr1;
	int		*nbr2;

	i = 0;
	init_redirections(p);
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
		{
			nbr1 = check_redir(tp.tab[i], '>');
			if (redir_errors(nbr1, nbr2, p))
				break ;
			p->redir_out += nbr1[0];
			p->redir_out_d += nbr1[1];
			nbr2 = check_redir(tp.tab[i], '<');
			if (redir_errors(nbr2, nbr1, p))
				break ;
			p->redir_in += nbr2[0];
			p->redir_in_d += nbr2[1];
			free_redirs(nbr1, nbr2);
		}
		i++;
	}
	p->redir = p->redir_in + p->redir_in_d + p->redir_out + p->redir_out_d;
}
