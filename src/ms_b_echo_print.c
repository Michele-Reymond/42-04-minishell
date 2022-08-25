/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_echo_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:52:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_dollar(char *var, char **args, int k, int i)
{
	printf("%s", var);
	if (how_many_in_str(&args[i][k + 1], '$') == 0 && args[i + 1] != NULL)
		printf(" ");
}

void print_variable(char **args, char **var, int i, int *j)
{
	int k;

	k = 0;
	while (args[i][k] != '\0')
	{
		while (args[i][k] != '\0' && args[i][k] != '$')
		{
			printf("%c", args[i][k]);
			k++;
		}
		if (args[i][k] == '$')
		{
			if (var[*j][0] != '\0')
				print_dollar(var[*j], args, k, i);
			(*j)++;
			k++;
			while (args[i][k] != '\0' && args[i][k] != ' ' 
				&& args[i][k] != '	' && args[i][k] != '$')
			{
				if (args[i][k] == '\'')
					printf("\'");
				k++;
			}
		}
	}
}

void	echo_print(char **args, char **var, int *print)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (print[i + 1] == 0 || print[i + 1] == 3 
				|| how_many_in_str(args[i], '$') == 0)
			printf("%s", args[i]);
		else
			print_variable(args, var, i, &j);
		if (args[i + 1] != NULL && print[i + 1] > 2 && args[i][0] != '$')
			printf(" ");
		i++;
	}
}
