/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:57 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 12:41:54 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*status_conversion(char *cmd, char *symbol)
{
	int		len;
	char	*tmp;
	char	*tmp2;
	char	*new;
	char	*status;

	len = ft_strlen(cmd) - ft_strlen(symbol);
	tmp = malloc(sizeof(char) * (len + 2));
	ft_bzero(tmp, len + 2);
	ft_strlcat(tmp, cmd, len + 1);
	status = ft_itoa(g_exit_status);
	tmp2 = ft_strjoin(tmp, status);
	if (symbol + 2)
	{
		symbol += 2;
		new = ft_strjoin(tmp2, symbol);
	}
	else
		new = ft_strdup(tmp2);
	ft_free(tmp);
	ft_free(tmp2);
	ft_free(status);
	return (new);
}

char	*multi_status_conv(char *tmp, char *old, char *symbol)
{
	char	*new;

	if (symbol != NULL)
		new = ft_strjoin(old, tmp);
	else
		new = ft_strdup(tmp);
	return (new);
}

// covertir le $? dans la commande
char	*exit_status_convert(char *cmd, char *symbol)
{
	char	*new;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	symbol = ft_strnstr(cmd, "$?", ft_strlen(cmd) + 1);
	if (symbol != NULL)
	{
		new = ft_strdup("");
		tmp3 = ft_strdup(cmd);
		while (symbol != NULL)
		{
			tmp = status_conversion(tmp3, symbol);
			symbol = ft_strnstr(tmp, "$?", ft_strlen(tmp) + 1);
			tmp2 = multi_status_conv(tmp, new, symbol);
			free(new);
			free(tmp3);
			new = tmp2;
			tmp3 = tmp;
		}
		free(tmp);
	}
	else
		new = ft_strdup(cmd);
	return (new);
}

void	exit_and_set_status(t_tab *t, char **cmds)
{
	long long	e_code;

	e_code = ft_atoll(cmds[1]);
	if (!(e_code - 1 > -9223372036854775807
			&& e_code - 1 < 9223372036854775807))
	{
		printf(MINISHELL ERRORS_EXIT "%s: " ERRORS_NUM, cmds[1]);
		g_exit_status = 255;
	}
	else if (e_code + 1 == -9223372036854775807)
		g_exit_status = 0;
	else if (cmds[1][0] == '-' && !args_if_alpha(&cmds[1][1]))
		g_exit_status = 256 + (e_code % 256);
	else if (!args_if_alpha(cmds[1])
		|| (!args_if_alpha(&cmds[1][1]) && cmds[1][0] == '+'))
		g_exit_status = e_code % 256;
	else
	{
		g_exit_status = 255;
		printf(MINISHELL ERRORS_EXIT "%s: " ERRORS_NUM, cmds[1]);
	}
	free_tabs(t, cmds);
	exit(g_exit_status);
}

//lancement de la commande exit et définition du status de sortie
void	ft_exit(char *cmd, t_tab *t)
{
	char	**cmds;
	char	**tmp;
	int		len;

	tmp = tokenize(cmd);
	cmds = clean_quotes_token(tmp, t->p);
	tabfree(tmp);
	len = tab_len(cmds);
	printf(EXIT);
	if (len == 1)
	{
		free_t_tab(t);
		tabfree(cmds);
		exit(g_exit_status);
	}
	else if (len > 2)
	{
		printf(MINISHELL ERRORS_EXIT ERRORS_EXIT_ARGS);
		tabfree(cmds);
		g_exit_status = 1;
		return ;
	}
	else if (len == 2)
		exit_and_set_status(t, cmds);
}
