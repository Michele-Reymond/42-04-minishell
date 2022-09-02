/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_p_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:38:04 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:21:50 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_outside_quotes(int *i, int nbr, char *cmd)
{
	while (cmd[*i] != '\0' && cmd[*i] != '\'' && cmd[*i] != '\"')
	{
		if (*i > 0 && (cmd[*i - 1] == ' ' || cmd[*i - 1] == '	'))
			nbr++;
		(*i)++;
	}
	return (nbr);
}

int	count_quotes(char *cmd, char stock, int i)
{
	int	nbr;

	nbr = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '	'
			&& cmd[i] != '\'' && cmd[i] != '\"')
			nbr++;
		nbr = count_outside_quotes(&i, nbr, cmd);
		if (cmd[i] == '\0')
			return (nbr);
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			nbr++;
			stock = cmd[i++];
		}
		while (cmd[i] != '\0' && cmd[i] != stock)
			i++;
		if (cmd[i] == '\0')
			return (nbr);
		else if (cmd[i++] == stock)
			stock = '\0';
	}
	return (nbr);
}

void	copy_outside_quotes(char *cmd, int *i, int *j, t_tprint new)
{
	int	tmp;
	int	y;

	while (cmd[*i] != '\0' && cmd[*i] != '\'' && cmd[*i] != '\"')
	{
		y = 0;
		tmp = *i;
		while (cmd[*i] != '\0' && cmd[*i] != ' ' && cmd[*i] != '	'
			&& cmd[*i] != '\'' && cmd[*i] != '\"')
			(*i)++;
		if (cmd[*i] == ' ' || cmd[*i] == '	')
			new.print[*j + 1] = 1;
		else
			new.print[*j + 1] = 0;
		new.tab[*j] = malloc(sizeof(char) * (*i - tmp + 1));
		*i = tmp;
		while (cmd[*i] != '\0' && cmd[*i] != ' ' && cmd[*i] != '	'
			&& cmd[*i] != '\'' && cmd[*i] != '\"')
			new.tab[*j][y++] = cmd[(*i)++];
		new.tab[*j][y] = '\0';
		(*j)++;
		if (cmd[*i] == ' ' || cmd[*i] == '	')
			(*i)++;
	}
}

int	stock_stock(char c, char *stock, int *tmp, int *i)
{
	if (c == '\0')
		return (1);
	else if (c == '\'' || c == '\"')
	{
		*stock = c;
		*tmp = *i;
		(*i)++;
	}
	return (0);
}

int	copy_inside_quotes(char *cmd, t_c *c, char *stock, t_tprint new)
{
	int	tmp;
	int	y;

	y = 0;
	if (stock_stock(cmd[c->i], stock, &tmp, &c->i))
		return (1);
	while (cmd[c->i] != '\0' && cmd[c->i] != *stock)
		(c->i)++;
	new.tab[c->j] = malloc(sizeof(char) * (c->i - tmp + 2));
	c->i = tmp;
	if (cmd[c->i] == '\'' || cmd[c->i] == '\"')
		new.tab[c->j][y++] = cmd[(c->i)++];
	while (cmd[c->i] != '\0' && cmd[c->i] != *stock)
		new.tab[c->j][y++] = cmd[(c->i)++];
	if (cmd[c->i] == *stock)
	{
		*stock = '\0';
		new.tab[c->j][y++] = cmd[(c->i)++];
	}
	if (cmd[c->i] == ' ' || cmd[c->i] == '	')
		new.print[c->j + 1] = 1;
	else
		new.print[c->j + 1] = 0;
	new.tab[c->j][y] = '\0';
	return (0);
}
