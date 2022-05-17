/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 07:50:39 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 15:26:01 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

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

int	ft_atoi(const char *str)
{
	long		i;
	long		result;
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
