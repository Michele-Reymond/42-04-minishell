/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:28:30 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/25 16:05:04 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	free_vartab(t_var *vartab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (vartab[i].key != NULL)
		{
			free(vartab[i].key);
			vartab[i].key = NULL;
		}
		if (vartab[i].value != NULL)
		{
			free(vartab[i].value);
			vartab[i].value = NULL;
		}
		i++;
	}
	if (vartab != NULL)
	{
		free(vartab);
		vartab = NULL;
	}
}

void	free_t_redirs(t_redir r)
{
	if (r.dest != NULL)
	{
		free(r.dest);
		r.dest = NULL;
	}
	if (r.redir != NULL)
	{
		free(r.redir);
		r.redir = NULL;
	}
	if (r.cmd != NULL)
	{
		free(r.cmd);
		r.cmd = NULL;
	}
}

void	free_all_t_redirs(t_redir *r, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (r[i].dest != NULL)
		{
			free(r[i].dest);
			r[i].dest = NULL;
		}
		if (r[i].redir != NULL)
		{
			free(r[i].redir);
			r[i].redir = NULL;
		}
		if (r[i].cmd != NULL)
		{
			free(r[i].cmd);
			r[i].cmd = NULL;
		}
		i++;
	}
	free(r);
}

void	free_redirs(int *nbr1, int *nbr2)
{
	if (nbr1 != NULL)
	{
		free(nbr1);
		nbr1 = NULL;
	}
	if (nbr2 != NULL)
	{
		free(nbr2);
		nbr2 = NULL;
	}
}
