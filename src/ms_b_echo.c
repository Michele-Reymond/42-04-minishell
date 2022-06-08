/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/07 13:28:44 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_print(char **args, char **var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '$')
		{
			printf("%s", var[j]);
			j++;
		}
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL && ft_strncmp(args[i + 1], "$ ", 2))
			printf(" ");
		i++;
	}
}

char	**echo_vars(char **token, t_tab t, int nbr)
{
	int i;
	int j;
	int pos;
	char **vars;
	char *tmp;

	i = 0;
	j = 0;
	pos = 0;
	vars = malloc(sizeof(char *) * nbr + 1);
	while (token[i] != NULL)
	{
		if (token[i][0] == '$')
		{
			if (token[i][1] == ' ')
				pos = var_exist(t.exp, &token[i][2]);
			else
				pos = var_exist(t.exp, &token[i][1]);
			if (pos == 0)
			{
				if (token[i][1] == ' ')
					pos = var_exist(t.var, &token[i][2]);
				else
					pos = var_exist(t.var, &token[i][1]);
				if (pos > 0)
					tmp = strdup(t.var[pos]);
			}
			else
				tmp = strdup(t.exp[pos]);
			if (pos == 0)
				vars[j] = strdup("");
			else
			{
				while (tmp && *tmp != '=')
					tmp++;
				tmp++;
				vars[j] = ft_strdup(tmp);
			}
			j++;
		}
		i++;
	}
	vars[j] = NULL;
	return (vars);
}

t_echo	echo_parsing(char **token, t_tab t)
{
	t_echo elem;
	int nbr_vars;
	int i;

	i = 1;
	if (!ft_strncmp(token[1], "-n", 2))
	{
		elem.flag = 'n';
		i++;
	}
	else
		elem.flag = '0';
	elem.args = tabdup(&token[i]);
	i = 0;
	while (elem.args[i])
		i++;
	elem.nbr_args = i;
	nbr_vars = how_many_in_tab(token, '$');
	if (nbr_vars == 0)
		elem.vars = NULL;
	else
		elem.vars = echo_vars(elem.args, t, nbr_vars);
	return (elem);
}

int	echo(char **token, t_tab t)
{
	t_echo elem;
	char **cleaned;

	cleaned = clean_quotes_token(token, t.p);
	if (tab_len(cleaned) < 2)
		elem.nbr_args = 0;
	else
		elem = echo_parsing(cleaned, t);
	if (elem.nbr_args == 0 && elem.flag != 'n')
		printf("\n");
	if (elem.nbr_args > 0 && elem.flag == 'n')
		echo_print(elem.args, elem.vars);
	if (elem.nbr_args > 0 && elem.flag != 'n')
	{
		echo_print(elem.args, elem.vars);
		printf("\n");
	}
	return (0);
}




	// t_echo		test;

	// test.cmd = "echo";
	// test.nbr_args = 3;
	// test.flag = ' ';
	// test.vars = NULL;
	// test.args = malloc(sizeof(char *) * 4);
	// test.args[0] = "bonjour";
	// test.args[1] = "les";
	// test.args[2] = "copains";
	// test.args[3] = NULL;
