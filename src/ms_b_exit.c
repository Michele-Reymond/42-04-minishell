/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:57 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/10 12:09:32 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *status_conversion(char *cmd, char *symbol)
{
	int len;
	char *tmp;
	char *tmp2;
	char *new;

	len = ft_strlen(cmd) - ft_strlen(symbol);
	tmp = malloc(sizeof(char) * len + 2);
	ft_strlcat(tmp, cmd, len + 1);
	tmp2 = ft_strjoin(tmp, ft_itoa(exit_status));
	if (symbol + 2)
	{
		symbol += 2;
		new = ft_strjoin(tmp2, symbol);
	}
	else
		new = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
	return (new);
}

char *multi_status_conv(char *tmp, char *old, char *symbol)
{
	char *new;

	if (symbol != NULL)
		new = ft_strjoin(old, tmp);
	else
		new = ft_strdup(tmp);
	return (new);
}

// covertir le $? dans la commande
char *exit_status_convert(char *cmd)
{
	char *new;
	char *tmp;
	char *tmp2;
	char *tmp3;
	char *symbol;

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
	}
	else
		new = ft_strdup(cmd);
	return (new);
}

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

long long	ft_atoll(const char *str)
{
	long	i;
	long long	result;
	long	signe;

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

int args_if_alpha(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}

void exit_and_set_status(t_tab *t, char **cmds, char *cmd)
{
	long long   e_code;

	e_code = ft_atoll(cmds[1]);
	if (!(e_code - 1 > -9223372036854775807
		&& e_code + 1 < 9223372036854775807))
	{
		printf(MINISHELL ERRORS_EXIT "%s: " ERRORS_NUM, cmds[1]);
		exit_status = 255;
	}
	else if (e_code + 1 == -9223372036854775807)
		exit_status = 0;
	else if (cmds[1][0] == '-' && !args_if_alpha(&cmds[1][1]))
		exit_status = 256 + (e_code % 256);
	else if (!args_if_alpha(cmds[1]) 
			|| (!args_if_alpha(&cmds[1][1]) && cmds[1][0] == '+'))
		exit_status = e_code % 256;
	else
	{
		exit_status = 1;
		printf(MINISHELL ERRORS_EXIT "%s: " ERRORS_NUM, cmds[1]);
	}
	free_tabs(t, cmds, cmd);
	exit(exit_status);
}

//lancement de la commande exit et définition du status de sortie
void ft_exit(char *cmd, t_tab *t)
{
    char        **cmds;
    char        **tmp;
    int         len;

    tmp = tokenize(cmd);
    cmds = clean_quotes_token(tmp, t->p);
	tabfree(tmp);
    len = tab_len(cmds);
    printf(EXIT);
    if (len == 1)
	{
		free_tabs(t, cmds, cmd);
        exit(exit_status);
	}
    else if (len > 2)
    {
        printf(MINISHELL ERRORS_EXIT ERRORS_EXIT_ARGS);
        exit_status = 1;
        return ;
    }
    else if (len == 2)
		exit_and_set_status(t, cmds, cmd);
}
