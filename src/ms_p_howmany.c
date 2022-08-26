/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_howmany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:57:09 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_in_tab(char **str, char c)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr + how_many_in_str(str[i], c);
		i++;
	}
	return (nbr);
}

int	how_many_in_str(char *str, char c)
{
	char	*pos;
	int		i;

	i = 0;
	pos = ft_strchr(str, c);
	while (pos)
	{
		pos++;
		pos = ft_strchr(pos, c);
		i++;
	}
	return (i);
}

int how_many_splits(char *str)
{
	int nbr;

	nbr = 0;
	nbr += how_many_in_str(str, '|');
	if (str[ft_strlen(str) - 1] != '|' && str[0] != '|')
		nbr++;
	if (str[ft_strlen(str) - 1] == '|' && str[0] == '|')
		nbr--;
	nbr += how_many_in_str(str, '|');
	return (nbr);
}

void init_redirections(t_parse *p)
{
	p->redir_out = 0;
	p->redir_out_d = 0;
	p->redir_in = 0;
	p->redir_in_d = 0;
}

int redir_errors(int *nbr1, int *nbr2, t_parse *p)
{
	if (nbr1[0] == -1 || nbr1[1] == -1)
	{
		p->redir_out = nbr1[0];
		p->redir_out_d = nbr1[1];
		if (nbr1 != NULL)
		{
			free(nbr1);
			nbr1 = NULL;
		}
		if (nbr2 != NULL)
		{
			free(nbr2);
			nbr2 = NULL;
		}
		return (1);
	}
	return (0);
}
