/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:57 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/20 15:53:15 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **exit_status_convert(char **token)
{
	char **new;
	char *tmp;
	char *tmp2;
	char *symbol;
	int i;
	int len;

	i = 0;
	new = malloc(sizeof(char *) * tab_len(token) + 2);
	while (token[i] != NULL)
	{
		symbol = ft_strnstr(token[i], "$?", ft_strlen(token[i]) + 1);
		if (symbol != NULL)
		{
			len = ft_strlen(token[i]) - ft_strlen(symbol);
			tmp = malloc(sizeof(char) * len + 2);
			ft_strlcat(tmp, token[i], len);
			tmp2 = ft_strjoin(tmp, ft_itoa(exit_status));
			if (symbol + 2)
			{
				symbol += 2;
				new[i] = ft_strjoin(tmp2, symbol);
			}
			else
				new[i] = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
		}
		else
			new[i] = ft_strdup(token[i]);
		i++;
	}
	new[i] = NULL;
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

char *replace_exit_status(char **token)
{
    char *new;
    char **tmp;

    tmp = exit_status_convert(token);
    new = tab_to_str(tmp);
    tabfree(tmp);
    return (new);
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

void ft_exit(char *cmd, t_tab *t)
{
    char        **cmds;
    char        **tmp;
    long long   e_code; 
    int         len;

    tmp = tokenize(cmd);
    cmds = clean_quotes_token(tmp, t->p);
    len = tab_len(cmds);
    printf(EXIT);
    if (len == 1)
        exit(exit_status);
    else if (len > 2)
    {
        printf(MINISHELL ERRORS_EXIT ERRORS_EXIT_ARGS);
        exit_status = 255;
        return ;
    }
    else if (len == 2)
    {
        e_code = ft_atoll(cmds[1]);
        if (!(e_code - 1 > -9223372036854775807 && e_code + 1 < 9223372036854775807))
        {
            printf(MINISHELL ERRORS_EXIT "%s: " ERRORS_NUM, cmds[1]);
            exit_status = 255;
        }
        else if (e_code + 1 == -9223372036854775807)
            exit_status = 0;
        else if (cmds[1][0] == '-' && !args_if_alpha(&cmds[1][1]))
            exit_status = 256 + (e_code % 256);
        else if (!args_if_alpha(cmds[1]) || (!args_if_alpha(&cmds[1][1]) && cmds[1][0] == '+'))
            exit_status = e_code % 256;
        else
            printf(MINISHELL ERRORS_EXIT "%s: " ERRORS_NUM, cmds[1]);
        exit(exit_status);
    }
}

// exit 72 > 72
// exit $? > valeur de $? (idem à exit tout court)
// exit coucou > 255
// bash: exit: machin: numeric argument required
// guillemets ok
