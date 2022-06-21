/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/21 17:56:10 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test d'un split qui stock les separateurs
static int	countwords_sep(char const *s, char c)
{
	int		i;
	int		words;
	size_t	sep;

	i = 0;
	words = 0;
	sep = 0;
	if (s[i] && s[i] != c)
		words++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			words++;
		if (s[i] == c)
			sep++;
		i++;
	}
	if (s[i - 1] == c)
		words--;
	if (words <= 0)
		words = 1;
	if (sep == ft_strlen(s))
		words = 0;
	return (words);
}

static int	copywords_sep(char **strtab, char const *s, char c, int words)
{
	int	len;
	int	i;
	int	y;
	int ok;

	len = 0;
	i = 0;
	y = 0;
	ok = 0;
	while (s[i] != '\0' && y < words)
	{
		len = 0;
		ok = 0;
		while (s[i] == c && s[i] != '\0')
		{
			i++;
			len++;
			ok = 1;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			len++;
		}
		strtab[y] = (char *)malloc(sizeof(char) * len + 2);
		if (!strtab[y])
			return (0);
		if (ok == 0)
			ft_strlcpy(strtab[y], &s[i - len], len + 1);
		else
		{
			ft_strlcpy(strtab[y], &s[i - len], len + 2);
			i++;
		}
		y++;
	}
	return (y);
}

char	**ft_split_with_sep(char const *s, char c)
{
	char	**strtab;
	int		y;
	int		words;

	y = 0;
	if (s == NULL)
		return (NULL);
	words = countwords_sep(s, c);
	strtab = (char **)malloc(sizeof(char *) * words + 1);
	if (!strtab)
		return (NULL);
	y = copywords_sep(strtab, s, c, words);
	strtab[y] = NULL;
	return (strtab);
}

// fin du test

static int	countwords(char const *s)
{
	int		i;
	int		words;
	size_t	sep;

	i = 0;
	words = 0;
	sep = 0;
	if (s[i] && (s[i] != ' ' || s[i] != '	'))
		words++;
	while (s[i] != '\0')
	{
		if ((s[i] == ' ' && s[i + 1] != ' ') || (s[i] == '	' && s[i + 1] != '	'))
			words++;
		if (s[i] == ' ' || s[i] == '	')
			sep++;
		i++;
	}
	if (s[i - 1] == ' ' || s[i - 1] == '	')
		words--;
	if (words <= 0)
		words = 1;
	if (sep == ft_strlen(s))
		words = 0;
	return (words);
}

static char	**copywords(char const *s, int words)
{
	char	**strtab;
	int	len;
	int	i;
	int	y;

	len = 0;
	i = 0;
	y = 0;
	strtab = (char **)malloc(sizeof(char *) * words + 1);
	if (!strtab)
		return (NULL);
	while (s[i] != '\0' && y < words)
	{
		len = 0;
		while ((s[i] == ' ' || s[i] == '	') && s[i] != '\0')
		{
			len++;
			i++;
		}
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '	')
		{
				i++;
				len++;
		}
		strtab[y] = (char *)malloc(sizeof(char) * len + 1);
		if (!strtab[y])
			return (0);
		ft_strlcpy(strtab[y], &s[i - len], len + 1);
		if ((s[i] == ' ' || s[i] == '	') && s[i] != '\0')
			i++;
		y++;
	}
	strtab[y] = NULL;
	return (strtab);
}

char	**ft_split_one_space(char const *s)
{
	char	**strtab;
	int		words;

	if (s == NULL)
		return (NULL);
	words = countwords(s);
	strtab = copywords(s, words);
	return (strtab);
}

void	echo_print(char **args, char **var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	display_tab(args);
	while (args[i] != NULL)
	{
		if (args[i][0] == '$' && how_many_in_str(args[i], ' ') == 0)
		{
			printf("%s", var[j]);
			j++;
		}
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL && ft_strncmp(args[i + 1], "$ ", 2))
			printf(" ");
		i++;
	}
}

char	**echo_vars(char **token, t_tab t, int nbr)
{
	int i;
	int j;
	int pos;
	char **vars;
	char *tmp;

	i = 0;
	j = 0;
	pos = 0;
	vars = malloc(sizeof(char *) * nbr + 1);
	while (token[i] != NULL)
	{
		if (token[i][0] == '$')
		{
			if (token[i][1] == ' ')
				pos = var_exist(t.exp, &token[i][2]);
			else
				pos = var_exist(t.exp, &token[i][1]);
			if (pos == 0)
				vars[j] = strdup("");
			else
			{
				tmp = strdup(t.exp[pos]);
				while (tmp && *tmp != '=')
					tmp++;
				tmp++;
				vars[j] = ft_strdup(tmp);
			}
			j++;
		}
		i++;
	}
	vars[j] = NULL;
	return (vars);
}

t_echo	echo_parsing(char **token, t_tab t)
{
	t_echo elem;
	int nbr_vars;
	int i;

	i = 1;
	if (!ft_strncmp(token[1], "-n", 2))
	{
		elem.flag = 'n';
		i++;
	}
	else
		elem.flag = '0';
	elem.args = tabdup(&token[i]);
	i = 0;
	while (elem.args[i])
		i++;
	elem.nbr_args = i;
	nbr_vars = how_many_in_tab(token, '$');
	if (nbr_vars == 0)
		elem.vars = NULL;
	else
		elem.vars = echo_vars(elem.args, t, nbr_vars);
	return (elem);
}

char **trim_tab(char **tab)
{
	char **new;
	char **tmp;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = 0;
	while (tab[i] != NULL)
	{
		if (!(how_many_in_str(tab[i], ' ') + how_many_in_str(tab[i], '	') == (int)ft_strlen(tab[i])))
			len++;
		i++;
	}
	i = 0;
	new = malloc(sizeof(char *) * len + 1);
	tmp = malloc(sizeof(char *) * tab_len(tab) + 1);
	while (tab[i] != NULL)
	{
		tmp[i] = ft_strtrim(tab[i], " 	");
		if (*tmp[i] != '\0')
		{
			new[j] = tmp[i];
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

char **split_quotes(char *cmd, char quote)
{
	char **new;
	char **tmp;
	char **tmp2;
	char *tmpstr;

	if (quote == '\'')
	{
		tmp = ft_split(cmd, quote);
		new = trim_tab(tmp);
	}
	else
	{
		tmp = ft_split(cmd, quote);
		tmp2 = trim_tab(tmp);
		tmpstr = tab_to_str(tmp2);
		tabfree(tmp2);
		new = ft_split_one_space(tmpstr);
		free(tmpstr);
	}
	tabfree(tmp);
	return (new);
}

// trouver les positions d'un caractère dans une string
// pos[0] correspond au nombre de c qu'il y a
// à partir de pos[1] cela correspond aux positions du caractère dans la string
int	*character_pos(char *str, char c)
{
	int i;
	int j;
	int nbr;
	int *pos;

	i = 0;
	j = 1;
	nbr = how_many_in_str(str, c);
	pos = malloc(sizeof(int) * nbr + 1);
	pos[0] = nbr;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			pos[j] = i;
			j++;
		}
		i++;
	}
	return (pos);
}

int check_if_in(char *cmd, char in, char out, int pos)
{
	int *q_out;
	int *q_in;
	int i;
	int j;

	i = 1;
	j = pos;
	q_in = character_pos(cmd, in);
	q_out = character_pos(cmd, out);
	while (i <= q_out[0])
	{
		j = pos;
		while (j <= q_in[0])
		{
			if (q_in[j] > q_out[i] && q_in[j] > q_out[i + 1])
				return (0);
			else if (q_in[j] > q_out[i] && q_in[j] < q_out[i + 1])
			{
				if (q_in[j + 1] < q_out[i + 1])
					return (q_in[j + 1]);
				else
					return (-1);
			}
			j += 2;
		}
		i += 2;
	}
	return (-2);
}

char **seperated_quotes(char *cmd)
{
	char **new;
	char **tmp;
	char **tmp2;
	char **tmp3;
	int i;
	
	i = 0;
	tmp = ft_split(cmd, '\'');
	tmp2 = trim_tab(tmp);
	tabfree(tmp);
	new = new_tab();
	while (tmp2[i] != NULL)
	{
		if (how_many_in_str(tmp2[i], '\"') > 0)
		{
			tmp3 = split_quotes(tmp2[i], '\"');
			tmp = tabjoin(new, tmp3);
			tabfree(new);
			new = tmp;
			tabfree(tmp3);
		}
		else
		{
			tmp = add_to_tab(new, tmp2[i]);
			tabfree(new);
			new = tmp;
		}
		i++;
	}
	return (new);
}

char **doubles_inside(char *cmd)
{
	char **new;
	char **tmp;
	char **tmp2;
	char **tmp3;
	char **tmp4;
	// int *printing;
	char *strtmp;
	int i;
	
	i = 0;
	tmp4 = ft_split_with_sep(cmd, '\'');
	tmp2 = trim_tab(tmp4);
	display_tab(tmp2);
	printf("---------\n");
	tabfree(tmp4);
	new = new_tab();
	while (tmp2[i] != NULL)
	{
		if (tmp2[i][0] == '\'' && tmp2[i][ft_strlen(tmp2[i]) - 1] == '\'')
		{
			strtmp = ft_strtrim(tmp2[i], "\'");
			tmp4 = add_to_tab(new, strtmp);
			tabfree(new);
			new = tmp4;
			free(strtmp);
		}
		else if (how_many_in_str(tmp2[i], '\"') > 0)
		{
			tmp3 = split_quotes(tmp2[i], '\"');
			exit(0);
			tmp = tabjoin(new, tmp3);
			tabfree(new);
			new = tmp;
			tabfree(tmp3);
		}
		else
		{
			tmp3 = tokenize(tmp2[i]);
			tmp = tabjoin(new, tmp3);
			tabfree(new);
			new = tmp;
			tabfree(tmp3);
		}
		i++;
	}
	// tmp = ft_split(cmd, '\'');
	// tmp2 = trim_tab(tmp);
	// tabfree(tmp);
	// new = malloc(sizeof(char *) * tab_len(tmp2) + 1);
	// while (tmp2[i] != NULL)
	// {
	// 	new[i] = ft_strtrim(tmp2[i], '\"')
	// 	i++;
	// }
	display_tab(new);
	exit(0);
	return (new);
}

char **split_all_quotes(char *cmd)
{
	int i;
	int j;
	int nbrdouble;
	int nbrsingle;
	char **new;

	i = -1;
	j = 1;
	nbrdouble = 0;
	nbrsingle = 0;
	while (i != -2)
	{
		if (i == -1)
			i++;
		nbrdouble += i;
		i = check_if_in(cmd, '\"',  '\'', j);
		if (i == -1)
			break ;
		j += 2;
	}

	i = -1;
	j = 1;
	while (i != -2)
	{
		if (i == -1)
			i++;
		nbrsingle += i;
		i = check_if_in(cmd, '\'',  '\"', j);
		if (i == -1)
			break ;
		j += 2;
	}

	if (nbrdouble == 0 && nbrsingle == 0)
		new = seperated_quotes(cmd);
	else if (nbrdouble > 0 && nbrsingle == 0)
		new = doubles_inside(cmd);
	else if (nbrdouble == 0 && nbrsingle > 0)
		printf("help\n");
	else
		printf("help\n");
	new = tokenize(cmd);
	return (new);
}

char **clean_cmd_for_echo(char *cmd, t_tab *t)
{
	char **new;

	if (t->p.double_q == 0 && t->p.single_q == 0)
		new = tokenize(cmd);
	else if (t->p.double_q > 0 && t->p.single_q == 0)
		new = split_quotes(cmd,  '\"');
	else if (t->p.double_q == 0 && t->p.single_q > 0)
		new = split_quotes(cmd, '\'');
	else
		new = split_all_quotes(cmd);
	return (new);
}

void	echo(char **token, t_tab t)
{
	t_echo elem;
	// char **cleaned;

	// cleaned = clean_quotes_token(token, t.p);
	if (tab_len(token) < 2)
		elem.nbr_args = 0;
	else
		elem = echo_parsing(token, t);
	if (elem.nbr_args == 0 && elem.flag != 'n')
		printf("\n");
	if (elem.nbr_args > 0 && elem.flag == 'n')
		echo_print(elem.args, elem.vars);
	if (elem.nbr_args > 0 && elem.flag != 'n')
	{
		echo_print(elem.args, elem.vars);
		printf("\n");
	}
	exit_status = 0;
}




	// t_echo		test;

	// test.cmd = "echo";
	// test.nbr_args = 3;
	// test.flag = ' ';
	// test.vars = NULL;
	// test.args = malloc(sizeof(char *) * 4);
	// test.args[0] = "bonjour";
	// test.args[1] = "les";
	// test.args[2] = "copains";
	// test.args[3] = NULL;
