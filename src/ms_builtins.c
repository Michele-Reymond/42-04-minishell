/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/07/25 12:43:19 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse the redirections caracteres > >> < <<
// return a int tab :
// nbr[0] : nbr of simple redir (> or <)
// nbr[1] : nbr of double redir (>> or <<)
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

int count_pipes(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
			nbr += how_many_in_str(tp.tab[i], '|');
		i++;
	}
	return (nbr);
}

int count_doubles(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 1 || tp.print[i + 1] == 4)
			nbr++;
		i++;
	}
	return (nbr);
}

int count_singles(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 0 || tp.print[i + 1] == 3)
			nbr++;
		i++;
	}
	return (nbr);
}

int count_dollar(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] != 0 && tp.print[i + 1] != 3)
			nbr += how_many_in_str(tp.tab[i], '$');
		i++;
	}
	return (nbr);
}

void count_redir(t_tprint tp, t_parse *p)
{
	int		i;
	int		*nbr1;
	int		*nbr2;

	i = 0;
	p->redir_out = 0;
	p->redir_out_d = 0;
	p->redir_in = 0;
	p->redir_in_d = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
		{
			nbr1 = check_redir(tp.tab[i], '>');
			if (nbr1[0] == -1 || nbr1[1] == -1)
			{
				p->redir_out = nbr1[0];
				p->redir_out_d = nbr1[1];
				if (nbr1)
				{
					free(nbr1);
					nbr1 = NULL;
				}
				if (nbr2)
				{
					free(nbr2);
					nbr2 = NULL;
				}
				break ;
			}
			p->redir_out += nbr1[0];
			p->redir_out_d += nbr1[1];
			nbr2 = check_redir(tp.tab[i], '<');
			if (nbr2[0] == -1 || nbr2[1] == -1)
			{
				p->redir_in = nbr2[0];
				p->redir_in_d = nbr2[1];
				if (nbr1)
				{
					free(nbr1);
					nbr1 = NULL;
				}
				if (nbr2)
				{
					free(nbr2);
					nbr2 = NULL;
				}
				break ;
			}
			p->redir_in += nbr2[0];
			p->redir_in_d += nbr2[1];
			if (nbr1)
			{
				free(nbr1);
				nbr2 = NULL;
			}
			if (nbr2)
			{
				free(nbr2);
				nbr2 = NULL;
			}
		}
		i++;
	}
	p->redir = p->redir_in + p->redir_in_d + p->redir_out + p->redir_out_d;
}


t_parse	stock_parsing_infos(t_tprint tp)
{
	t_parse	p;
	
	p.pipes = count_pipes(tp);
	p.nbr_cmd = p.pipes + 1;
	p.double_q = count_doubles(tp);
	p.single_q = count_singles(tp);
	p.dollar = count_dollar(tp);
	count_redir(tp, &p);
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
	(void) p;
	
	cmds = clean_spaces(cmd);
	// autres clean a faire?
	return (cmds);
}

// créer un tableau de commandes sans les espaces
char	**clean_spaces(char *cmd)
{
	char	**cmds;
	char	**tmp;
	int		i;

	i = 0;
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

char *add_quotes(char *old, char quote)
{
	char *new;
	int i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(old) + 3);
	new[0] = quote;
	while (old[i] != '\0')
	{
		new[i + 1] = old[i];
		i++;
	}
	new[i + 1] = quote;
	new[i + 2] = '\0';
	return (new);
}

char *join_strings(t_tprint tp, int pos, int start)
{
	int i;
	char *tmp2;
	char *tmp3;
	char *new;

	i = start;
	new = ft_strdup("");
	while (tp.tab[i] != NULL && i < pos)
	{
		tmp2 = ft_strjoin(new, tp.tab[i]);
		if (tp.tab[i + 1] != NULL && tp.print[i + 1] > 2)
		{
			tmp3 = ft_strjoin(tmp2, " ");
			free(new);
			free(tmp2);
			new = tmp3;
		}
		else
		{
			free(new);
			new = tmp2;
		}
		i++;
	}
	return (new);
}

int how_many_splits(char *str)
{
	// char *tmp;
	int nbr;

	nbr = 0;
	nbr += how_many_in_str(str, '|');
	if (str[ft_strlen(str) - 1] != '|' && str[0] != '|')
		nbr++;
	if (str[ft_strlen(str) - 1] == '|' && str[0] == '|')
		nbr--;
	nbr += how_many_in_str(str, '|');
	// tmp = ft_strchr(str, '|');
	// if (tmp != str)
	// 	nbr++;
	// if (tmp == NULL)
	// 	return (0);
	// else
	// 	nbr++;
	// while (tmp != NULL)
	// {
	// 	tmp++;
	// 	tmp = ft_strchr(tmp, '|');
	// 	nbr += 2;
	// }
	return (nbr);
}

int count_multi_pipes_cmds(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != 0)
	{
		if (how_many_in_str(tp.tab[i], '|') > 0 && (tp.print[i + 1] == 2 || tp.print[i + 1] == 5) && ft_strlen(tp.tab[i]) > 1)
		{
			nbr += how_many_in_str(tp.tab[i], '|');
			if (tp.tab[i][ft_strlen(tp.tab[i]) - 1] != '|' && tp.tab[i][0] != '|')
				nbr++;
			if (tp.tab[i][ft_strlen(tp.tab[i]) - 1] == '|' && tp.tab[i][0] == '|')
				nbr--;
			nbr += how_many_in_str(tp.tab[i], '|');
		}
		i++;
	}
	return (nbr);
}

char **split_out(char *str)
{
	char **new;
	int nbr;
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	start = 0;
	nbr = how_many_splits(str);
	new = malloc(sizeof(char *) * (nbr + 1));
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\0' && str[i] != '|')
			i++;
		if (i > start)
		{
			new[j] = ft_strldup(&str[start], i - start + 1);
			j++;
		}
		if (str[i] == '|')
		{
			new[j] = ft_strdup("|");;
			j++;
		}
		if (str[i] != '\0')
			i++;
	}
	new[j] = NULL;
	return (new);
}

t_tprint split_pipes_phase_1(t_tprint tp)
{
	int i;
	int j;
	int k;
	char **splitted;
	char **tmp;
	t_tprint last;
	char *quoted;
	int pipes;

	i = 0;
	j = 1;
	last.tab = new_tab();
	pipes = count_multi_pipes_cmds(tp);
	last.print = malloc(sizeof(char *) * (pipes + tp.print[0] + 1));
	last.print[0] = pipes + tp.print[0];
	while (tp.tab[i] != NULL)
	{
		if(how_many_in_str(tp.tab[i], '|') > 0 && (tp.print[i + 1] == 2 || tp.print[i + 1] == 5) && ft_strlen(tp.tab[i]) > 1)
		{
			splitted = split_out(tp.tab[i]);
			tmp = tabjoin(last.tab, splitted);
			k = 0;
			while (k < tab_len(splitted) - 1)
			{
				last.print[j] = 2;
				j++;
				k++;
			}
			if (tp.print[i + 1] == 2)
				last.print[j] = 2;
			else
				last.print[j] = 5;
			j++;
			tabfree(last.tab);
			tabfree(splitted);
			last.tab = tmp;
		}
		else
		{
			if (tp.print[i + 1] == 1 && i != 0)
			{
				last.print[j] = 1;
				quoted = add_quotes(tp.tab[i], '\"');
			}
			else if (tp.print[i + 1] == 4 && i != 0)
			{
				last.print[j] = 4;
				quoted = add_quotes(tp.tab[i], '\"');
			}
			else if (tp.print[i + 1] == 0 && i != 0)
			{
				last.print[j] = 0;
				quoted = add_quotes(tp.tab[i], '\'');
			}
			else if (tp.print[i + 1] == 3 && i != 0)
			{
				last.print[j] = 3;
				quoted = add_quotes(tp.tab[i], '\'');
			}
			else if (tp.print[i + 1] == 5)
			{
				last.print[j] = 5;
				quoted = ft_strdup(tp.tab[i]);
			}
			else
			{
				last.print[j] = 2;
				quoted = ft_strdup(tp.tab[i]);
			}
			tmp = add_to_tab(last.tab, quoted);
			tabfree(last.tab);
			free(quoted);
			quoted = NULL;
			last.tab = tmp;
			tmp = NULL;
			j++;
		}
		i++;
	}
	tmp = add_to_tab(last.tab, "");
	tabfree(last.tab);
	last.tab = tmp;
	last.tab[tab_len(tmp) - 1] = NULL;
	return (last);
}

int check_doubles_pipes(t_tprint tp)
{
	int i;

	i = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.tab[i][0] == '|' && tp.tab[i + 1][0] == '|' 
			&& (tp.print[i + 2] == 2 || tp.print[i + 1] == 5)
			&& (tp.print[i + 2] == 2 || tp.print[i + 1] == 5))
			{
				printf(ERROR_UNEXPECTED_TOKEN);
				if (tp.tab[i + 2][0] == '|')
					printf("\'||\'\n");
				else
					printf("\'|\'\n");
				exit_status = 258;
				return (1);
			}
		i++;
	}
	return (0);
}

char **split_pipes(t_tprint tp, int pipes)
{
	int i;
	int start;
	int j;
	t_tprint splitted;
	char **new;

	i = 0;
	j = 0;
	start = 0;
	splitted = split_pipes_phase_1(tp);
	if (check_doubles_pipes(splitted))
		return (NULL);
	new = malloc(sizeof(char *) * (pipes + 2));
	while (splitted.tab[i] != NULL)
	{
		start = i;
		while (splitted.tab[i] != NULL && !(splitted.tab[i][0] == '|' && ft_strlen(splitted.tab[i]) == 1))
			i++;
		if (i > start)
		{
			new[j] = join_strings(splitted, i, start);
			j++;
		}
		if (splitted.tab[i] != NULL)
			i++;
	}
	tabfree(splitted.tab);
	new[j] = NULL;
	return (new);
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
	i = 0;
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

int check_closed_quotes(t_tprint tp)
{
	int i;

	i = 1;
	while (i <= tp.print[0])
	{
		if(tp.print[i] == -1)
		{
			printf(ERROR_QUOTES);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor(char *cmd, t_tab *t)
{
	t_parse		p;
	t_tprint	tp;
	
	tp = parsing_master(cmd);
	if (check_closed_quotes(tp))
		return (1);
	p = stock_parsing_infos(tp);
	if (!(p.redir_in >= 0 && p.redir_out >= 0))
		return (1);
	t->p = p;
	p.cmds = split_pipes(tp, p.pipes);
	if (p.cmds == NULL)
		return (1);
	if (tab_len(p.cmds) == 1 && p.redir == 0)
	{
		if (launch_cmds(p.cmds[0], t))
			other_with_fork(p.cmds[0], t);
	}
	else if (p.pipes > 0 && p.redir == 0)
		launch_with_pipes(p, t);
	else if (p.redir > 0)
		launch_with_redir(p, t);
	return (0);
}

int	launch_cmds(char *cmd, t_tab *t)
{
	t_tprint tp;

	tp = parsing_master(cmd);
	if (!ft_strncmp(cmd, "exit", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		ft_exit(cmd, t);
	else if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		t = ms_b_cd(tp, t);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		echo(tp, *t);
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		t = ft_export(t, tp);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		t = unset(t, tp);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		display_env(t->env);
	else
		return (1);
	return (0);
}

int	is_a_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
		return (1);
	else if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (1);
	else
		return (0);
}

int	launch_builtins_with_redir(char *cmd, t_tab *t, int fd, int std)
{
	int ret;

	dup2(fd, std);
	ret = launch_cmds(cmd, t);
	return (ret);
}

int	launch_builtins_with_doors(char *cmd, t_tab *t, t_doors doors)
{
	int ret;

	dup2(doors.in, STDIN_FILENO);
	dup2(doors.out, STDOUT_FILENO);
	ret = launch_cmds(cmd, t);
	return (ret);
}
