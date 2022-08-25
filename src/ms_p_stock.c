/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_stock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 17:09:01 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *too_much_redirs(char *tmp, char redir)
{
	int		*nbr;

	nbr = malloc(sizeof(int) * 2);
	nbr[0] = 0;
	nbr[1] = 0;
	printf(ERROR_UNEXPECTED_TOKEN);
	if (tmp + 3 && *(tmp + 3) == redir)
		printf("`%c%c'\n", redir, redir);
	else
		printf("`%c'\n", redir);
	nbr[0] = -1;
	nbr[1] = -1;
	return (nbr);
}

int *init_nbr_redir(void)
{
	int		*nbr;

	nbr = malloc(sizeof(int) * 2);
	nbr[0] = 0;
	nbr[1] = 0;
	return (nbr);
}
// parse the redirections caracteres > >> < <<
// return a int tab :
// nbr[0] : nbr of simple redir (> or <)
// nbr[1] : nbr of double redir (>> or <<)
int	*check_redir(char *cmd, char redir)
{
	char	*tmp;
	int		*nbr;
	
	nbr = init_nbr_redir();
	tmp = ft_strchr(cmd, redir);
	while (tmp != NULL)
	{
		if (tmp + 1 && tmp + 2 && *(tmp + 1) == redir && *(tmp + 2) == redir)
			return (too_much_redirs(tmp, redir));
		if (tmp + 1 && *(tmp + 1) == redir)
		{
			nbr[1]++;
			tmp += 2;
		}
		else if (tmp && *tmp == redir)
			if ( *(tmp + 1) != redir && (tmp == cmd || *(tmp - 1) != redir))
			{
				nbr[0]++;
				tmp++;
			}
		tmp = ft_strchr(tmp, redir);
	}
	return (nbr);
}

t_parse	stock_parsing_infos(t_tprint tp)
{
	t_parse	p;
	
	p.pipes = count_pipes(tp);
	p.nbr_cmd = p.pipes + 1;
	p.double_q = count_doubles(tp);
	p.single_q = count_singles(tp);
	p.dollar = count_dollar(tp);
	p.cmds = NULL;
	count_redir(tp, &p);
	return (p);
}