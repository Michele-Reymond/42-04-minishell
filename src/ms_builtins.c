/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/03 18:03:07 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse the redirections caracteres > >> < <<
int	*check_redir(char *cmd, char redir)
{
	char	*tmp;
	int		*nbr;
	
	nbr = malloc(sizeof(int) * 2);
	nbr[0] = 0;
	nbr[1] = 0;
	tmp = ft_strchr(cmd, redir);
	while (tmp != NULL)
	{
		if (tmp + 1 && tmp + 2 && *(tmp + 1) == redir && *(tmp + 2) == redir)
		{
			printf(ERROR_UNEXPECTED_TOKEN);
			if (tmp + 3 && *(tmp + 3) == redir)
				printf("`%c%c'\n", redir, redir);
			else
				printf("`%c'\n", redir);
			nbr[0] = -1;
			nbr[1] = -1;
			return (nbr);
		}
		if (tmp + 1 && *(tmp + 1) == redir)
		{
			nbr[1]++;
			cmd = tmp;
			tmp += 2;
		}
		else if (tmp && *tmp == redir)
			if (*(tmp + 1) != redir && *(tmp - 1) != redir)
			{
				nbr[0]++;
				cmd = tmp;
				tmp++;
			}
		tmp = ft_strchr(tmp, redir);
	}
	return (nbr);
}

t_parse	stock_parsing_infos(char *cmd)
{
	t_parse	p;
	int		*nbr1;
	int		*nbr2;
	
	p.redir_in = 0;
	p.redir_out = 0;
	p.redir_in_d = 0;
	p.redir_out_d = 0;
	p.pipes = how_many_in_str(cmd, '|');
	p.nbr_cmd = p.pipes + 1;
	p.double_q = how_many_in_str(cmd, '\"');
	p.single_q = how_many_in_str(cmd, '\'');
	p.dollar = how_many_in_str(cmd, '$');
	nbr1 = check_redir(cmd, '>');
	p.redir_out = nbr1[0];
	p.redir_out_d = nbr1[1];
	nbr2 = check_redir(cmd, '<');
	p.redir_in = nbr2[0];
	p.redir_in_d = nbr2[1];
	return (p);
}

int	pre_parsing_errors(char *cmd, t_parse p)
{
	(void) cmd;
	if (!(p.redir_in >= 0 && p.redir_out >= 0))
		return (1);
	if (p.double_q % 2 != 0)
	{
		printf(ERROR_QUOTES);
		return (1);
	}
	if (p.single_q % 2 != 0)
	{
		printf(ERROR_QUOTES);
		return (1);
	}
	return (0);
}

// créer un tableau de commandes clean
char	**clean_cmds(char *cmd, t_parse p)
{
	char	**cmds;
	// char	**tmp;
	
	cmds = clean_spaces(cmd, p);
	// autres clean a faire?
	return (cmds);
}

// créer un tableau de commandes sans les espaces
char	**clean_spaces(char *cmd, t_parse p)
{
	char	**cmds;
	char	**tmp;
	int		i;

	i = 0;
	(void) p;
	tmp = ft_split(cmd, '|');
	cmds = malloc(sizeof(char *) * tab_len(tmp) + 1);
	while (tmp[i] != NULL)
	{
		cmds[i] = ft_strtrim(tmp[i], " ");
		i++;
	}
	cmds[i] = NULL;
	tabfree(tmp);
	return (cmds);
}

char	*tab_to_str(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	while (tab[i] != NULL)
	{
		if (*tab[i] == '\0')
		{
			str = ft_strjoin(tmp, " ");
			free(tmp);
			tmp = str;
		}
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free(tmp);
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free(tmp);
			tmp = str;
		}
		i++;
	}
	return (str);
}

char	**clean_quotes(char **cmds, t_parse p)
{
	char	**new;
	char	**token;
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (p.double_q == 0 && p.single_q == 0)
		return (cmds);
	new = malloc(sizeof(char *) * tab_len(cmds) + 1);
	while (cmds[j] != NULL)
	{
		i = 0;
		tmp = tokenize(cmds[j]);
		token = malloc(sizeof(char *) * tab_len(tmp) + 1);
		while (tmp[i] != NULL)
		{
			token[i] = ft_strtrim(tmp[i], "\"");
			i++;
		}
		token[i] = NULL;
		new[j] = tab_to_str(token);
		j++;
	}
	return (cmds);
}

char	**clean_quotes_token(char **token, t_parse p)
{
	char	**new;
	int		i;
	//int		j;

	i = 0;
	//j = 0;
	if (p.double_q == 0 && p.single_q == 0)
		return (token);
	new = malloc(sizeof(char *) * tab_len(token) + 1);
	while (token[i] != NULL)
	{
		if (*token[i] == '\0')
			new[i] = ft_strdup(" ");
		else
			new[i] = ft_strtrim(token[i], "\"");
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	monitor(char *cmd, t_tab *t)
{
	t_parse	p;
	
	p = stock_parsing_infos(cmd);
	t->p = p;
	if (pre_parsing_errors(cmd, p))
		return (1);
	p.cmds = clean_spaces(cmd, p);

	// TO DO > faire une fonction qui verifie les commandes

	// printf("%s\n", cmd);
	// printf("< : %d\n", p.redir_in);
	// printf("<< : %d\n", p.redir_in_d);
	// printf("> : %d\n", p.redir_out);
	// printf(">> : %d\n", p.redir_out_d);
	// printf("| : %d\n", p.pipes);
	
	if (tab_len(p.cmds) == 1)
		launch_cmds(p.cmds[0], t);
	return (0);
}

int	launch_cmds(char *cmd, t_tab *t)
{
	char	**token;

	token = tokenize(cmd);
	if (!ft_strncmp(cmd, "cd", 2))
		t = ms_b_cd(cmd, t);
	else if (!ft_strncmp(cmd, "pwd", 3))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo(token, *t);
	else if (!ft_strncmp(cmd, "export", 6))
		t = ft_export(t, token);
	else if (!ft_strncmp(cmd, "unset", 5))
		t = unset_var(t, token);
	else if (!ft_strncmp(cmd, "env", 3))
		display_env(t->env);
	else
		ms_b_other(cmd);
	return (0);
}
