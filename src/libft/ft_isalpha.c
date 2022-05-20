/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 08:42:59 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 14:50:05 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	int	res;

	res = 0;
	if (c > 64 && c < 91)
		res = 1;
	if (c > 96 && c < 123)
		res = 1;
	return (res);
}