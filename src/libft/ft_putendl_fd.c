/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:08:33 by vroch             #+#    #+#             */
/*   Updated: 2021/11/14 12:23:30 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	if (*s != 0)
	{
		len = 0;
		len = ft_strlen(s);
		if (len != 0)
		{
			write (fd, s, len);
		}
		write (fd, "\n", 1);
	}
}
