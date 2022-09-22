/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:11:58 by vroch             #+#    #+#             */
/*   Updated: 2022/09/22 14:43:04 by mreymond         ###   ########.fr       */
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
