/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 08:21:01 by vroch             #+#    #+#             */
/*   Updated: 2021/11/12 14:50:30 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	int	res;

	res = 0;
	if (c > 64 && c < 91)
		res = 1;
	if (c > 96 && c < 123)
		res = 1;
	if (c > 47 && c < 58)
		res = 1;
	return (res);
}
