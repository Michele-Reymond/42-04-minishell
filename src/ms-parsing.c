/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 16:23:25 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize(char *buff)
{
	char	**token;
	char	*pos;

	if (buff == NULL)
		return (new_tab());
	pos = ft_strchr(buff, '\t');
	while (pos)
	{
		*pos = ' ';
		pos = ft_strchr(pos, '\t');
	}
	token = ft_split(buff, ' ');
	return (token);
}

int	how_many_in_tab(char **str, char c)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr + how_many_in_str(str[i], c);
		i++;
	}
	return (nbr);
}

int	how_many_in_str(char *str, char c)
{
	char	*pos;
	int		i;

	i = 0;
	pos = ft_strchr(str, c);
	while (pos)
	{
		pos++;
		pos = ft_strchr(pos, c);
		i++;
	}
	return (i);
}
