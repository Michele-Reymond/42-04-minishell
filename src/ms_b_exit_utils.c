/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:57 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 14:39:58 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pass(char s)
{
	if (s == '\n' || s == '\t' || s == '\v' || s == '\f' || s == '\r')
	{
		return (1);
	}
	if (s == ' ')
	{
		return (1);
	}
	return (0);
}

long long	ft_atoll(const char *str)
{
	long		i;
	long long	result;
	long		signe;

	result = 0;
	signe = 1;
	i = 0;
	while (str[i] != '\0' && ft_pass(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		signe = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	result = result * signe;
	return (result);
}

int	args_if_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
