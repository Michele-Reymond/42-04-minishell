/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:24:00 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_tab_and_int(int *inttab, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (inttab == NULL || tab == NULL)
		return ;
	while (tab[i] != NULL && j <= inttab[0])
	{
		printf("%d: ", inttab[j]);
		printf("%s\n", tab[i]);
		i++;
		j++;
	}
}

char	copy_and_increase(char c, int *i, int *y)
{
	(*i)++;
	(*y)++;
	return (c);
}

void	trim_single_and_tprint(t_tprint tmp, t_tprint *tp, int i)
{
	tp->tab[i] = ft_strtrim(tmp.tab[i], "\'");
	if (tmp.print[i + 1] == 1)
		tp->print[i + 1] = 3;
	else
		tp->print[i + 1] = 0;
}

void	trim_doubles_and_tprint(t_tprint tmp, t_tprint *tp, int i)
{
	tp->tab[i] = ft_strtrim(tmp.tab[i], "\"");
	if (tmp.print[i + 1] == 1)
		tp->print[i + 1] = 4;
	else
		tp->print[i + 1] = 1;
}

void	trim_and_tprint_else(t_tprint tmp, t_tprint *tp, int i)
{
	tp->tab[i] = ft_strdup(tmp.tab[i]);
	if (tmp.print[i + 1] == 1)
		tp->print[i + 1] = 5;
	else
		tp->print[i + 1] = 2;
}
