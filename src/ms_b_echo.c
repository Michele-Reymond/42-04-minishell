/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:52:08 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ici tab ne commence pas avec la commande echo
// on commance donc l'index de print à 2
char	**echo_vars(char **tab, t_tab t, int nbr, int *print)
{
	int i;
	int j;
	char **vars;
	char *tmp;

	i = 0;
	j = 0;
	vars = malloc(sizeof(char *) * (nbr + 1));
	while (tab[i] != NULL)
	{
		if (print[i + 1] != 0 && print[i + 1] != 3)
		{
			tmp = ft_strchr(tab[i], '$');
			while (tmp != NULL)
			{
				tmp = copy_variables(tmp, vars, j, t);
				j++;
			}
		}
		i++;
	}
	free(tmp);
	vars[j] = NULL;
	return (vars);
}

t_echo	echo_parsing(char **tab, t_tab t, int *print)
{
	t_echo elem;
	int nbr_vars;
	int i;

	i = 1;
	if (!ft_strncmp(tab[1], "-n", 2) && ft_strlen(tab[1]) == 2)
	{
		elem.flag = 'n';
		i++;
	}
	else
		elem.flag = '0';
	elem.args = tabdup(&tab[i]);
	elem.spaces = copy_spaces_tab(print);
	i = 0;
	while (elem.args[i] != NULL)
		i++;
	elem.nbr_args = i;
	nbr_vars = how_many_dollars(tab, print);
	if (nbr_vars == 0)
		elem.vars = NULL;
	else
		elem.vars = echo_vars(tab, t, nbr_vars, print);
	return (elem);
}

void	echo(t_tprint tp, t_tab t)
{
	t_echo elem;
	
	elem.flag = '\0';
	if (tab_len(tp.tab) < 2)
		elem.nbr_args = 0;
	else
		elem = echo_parsing(tp.tab, t, tp.print);
	if (elem.nbr_args == 0 && elem.flag != 'n')
		printf("\n");
	if (elem.nbr_args > 0 && elem.flag == 'n')
		echo_print(elem.args, elem.vars, elem.spaces);
	if (elem.nbr_args > 0 && elem.flag != 'n')
	{
		echo_print(elem.args, elem.vars, elem.spaces);
		printf("\n");
	}
	if (!(tab_len(tp.tab) < 2))
		free_elem(elem);
	exit_status = 0;
}
