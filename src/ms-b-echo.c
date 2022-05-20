/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/20 14:38:38 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour le parsing voir l'onglet parsing de Notion

void	echo_print(char **args, char **var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '$' && ft_strlen(args[i]) == 1)
		{
			printf("%s", var[j]);
			j++;
		}
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	echo(unsigned int nbr_arg, char flag, char **args, char **var)
{
	if (nbr_arg == 0 && flag != 'n')
		printf("\n");
	else if (nbr_arg > 0 && flag == 'n')
		echo_print(args, var);
	else if (nbr_arg > 0 && flag != 'n')
	{
		echo_print(args, var);
		printf("\n");
	}
	else
		return (0);
	return (0);
}
