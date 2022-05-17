/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:11:58 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 11:39:59 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlen(const char *str)
{
	unsigned long int	res;

	if (*str == 0)
		return (0);
	res = 0;
	while (str[res])
		res++;
	return (res);
}
