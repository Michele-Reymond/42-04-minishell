/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/13 11:32:47 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strldup(const char *src, size_t dstsize)
{
	size_t	i;
	char	*dst;
	char	*ptr;

	i = 0;
	if (dstsize == 0)
		return (NULL);
	ptr = (char *)src;
	dst = malloc(sizeof(char) * (dstsize + 1));
	if (dst == NULL)
		return (NULL);
	while (ptr[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = ptr[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void print_dollar(char *var, char **args, int k, int i)
{
	printf("%s", var);
	if (how_many_in_str(&args[i][k + 1], '$') == 0 && args[i + 1] != NULL)
		printf(" ");
}

void print_variable(char **args, char **var, int i, int *j)
{
	int k;

	k = 0;
	while (args[i][k] != '\0')
	{
		while (args[i][k] != '\0' && args[i][k] != '$')
		{
			printf("%c", args[i][k]);
			k++;
		}
		if (args[i][k] == '$')
		{
			if (var[*j][0] != '\0')
				print_dollar(var[*j], args, k, i);
			(*j)++;
			k++;
			while (args[i][k] != '\0' && args[i][k] != ' ' 
				&& args[i][k] != '	' && args[i][k] != '$')
			{
				if (args[i][k] == '\'')
					printf("\'");
				k++;
			}
		}
	}
}

void	echo_print(char **args, char **var, int *print)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (print[i + 1] == 0 || print[i + 1] == 3 
				|| how_many_in_str(args[i], '$') == 0)
			printf("%s", args[i]);
		else
			print_variable(args, var, i, &j);
		if (args[i + 1] != NULL && print[i + 1] > 2 && args[i][0] != '$')
			printf(" ");
		i++;
	}
}

char *find_key(char *str)
{
	int i;
	char *key;
	
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != '\'')
		i++;
	key = ft_strldup(&str[1], i);
	return (key);
}

char	*export_to_var(char *str)
{
	char	*var;

	while (*str != '\0' && *str != '=')
		str++;
	if (*str == '\0')
		var = ft_strdup("");
	else
	{
		str += 2;
		var = ft_strldup(str, ft_strlen(str));
	}
	return(var);
}

char *copy_variables(char *tmp, char **vars, int j, t_tab t)
{
	char *key;
	int pos;

	key = find_key(tmp);
	pos = var_exist(t.exp, key);
	if (pos == 0)
		vars[j] = ft_strdup("");
	else
		vars[j] = export_to_var(t.exp[pos]);
	tmp++;
	tmp = ft_strchr(tmp, '$');
	return (tmp);
}

// ici tab ne commence pas avec la commande echo
// on commance donc l'index de print à 2
char	**echo_vars(char **tab, t_tab t, int nbr, int *print)
{
	int i;
	int j;
	char **vars;
	char *tmp;

	i = 0;
	j = 0;
	vars = malloc(sizeof(char *) * (nbr + 1));
	while (tab[i] != NULL)
	{
		if (print[i + 1] != 0 && print[i + 1] != 3)
		{
			tmp = ft_strchr(tab[i], '$');
			while (tmp != NULL)
			{
				tmp = copy_variables(tmp, vars, j, t);
				j++;
			}
		}
		i++;
	}
	vars[j] = NULL;
	return (vars);
}

int how_many_dollars(char **tab, int *print)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (tab[i] != NULL && i <= print[0])
	{
		if (print[i + 1] != 0 && print[i + 1] != 3)
			nbr = nbr + how_many_in_str(tab[i], '$');
		i++;
	}
	return (nbr);
}

int *copy_spaces_tab(int *print)
{
	int i;
	int j;
	int *new;

	i = 1;
	j = 2;
	new = malloc(sizeof(int) * print[0]);
	new[0] = print[0] - 1;
	while (i <= print[0])
	{
		new[i] = print[j];
		i++;
		j++;
	}
	return (new);
}

t_echo	echo_parsing(char **tab, t_tab t, int *print)
{
	t_echo elem;
	int nbr_vars;
	int i;

	i = 1;
	if (!ft_strncmp(tab[1], "-n", 2) && ft_strlen(tab[1]) == 2)
	{
		elem.flag = 'n';
		i++;
	}
	else
		elem.flag = '0';
	elem.args = tabdup(&tab[i]);
	elem.spaces = copy_spaces_tab(print);
	while (elem.args[i])
		i++;
	elem.nbr_args = i;
	nbr_vars = how_many_dollars(tab, print);
	if (nbr_vars == 0)
		elem.vars = NULL;
	else
		elem.vars = echo_vars(tab, t, nbr_vars, print);
	return (elem);
}

// la premiere valeur du tableau d'int est le nombre d'int qu'il contient sauf le premier
int *add_to_inttab(int *printing, int add)
{
	int *new;
	int i;

	i = 1;
	new = malloc(sizeof(int) * (printing[0] + 1));
	new[0] = printing[0] + 1;
	while (i <= printing[0])
	{
		new[i] = printing[i];
		i++;
	}
	new[i] = add;
	return (new);
}

// la premiere valeur du tableau d'int est le nombre d'int qu'il contient sauf le premier
int *new_inttab(void)
{
	int *new;

	new = malloc(sizeof(int) * 1);
	new[0] = 0;
	return (new);
}

// la premiere valeur du tableau d'int est le nombre d'int qu'il contient sauf le premier
int *fill_inttab(int *inttab, int add, int nbr)
{
	int *new;
	int i;
	int j;

	i = 1;
	j = 0;
	new = malloc(sizeof(int) * (inttab[0] + nbr));
	new[0] = inttab[0] + nbr;
	while (i <= inttab[0])
	{
		new[i] = inttab[i];
		i++;
	}
	while (j < nbr)
	{
		new[i] = add;
		j++;
		i++;
	}
	return (new);
}

int *inttabdup(int *inttab)
{
	int i;
	int *new;

	i = 0;
	new = malloc(sizeof(int) * (inttab[0] + 1));
	while (i <= inttab[0])
	{
		new[i] = inttab[i];
		i++;
	}
	return (new);
}

void display_inttab(int *inttab)
{
	int i;

	i = 1;
	while (i <= inttab[0])
	{
		printf("%d\n", inttab[i]);
		i++;
	}
}

void display_tab_and_int(int *inttab, char **tab)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (inttab == NULL || tab == NULL)
		return ;
	while (tab[i] != NULL && j <= inttab[0])
	{
		printf("%d: ", inttab[j]);
		printf("%s\n", tab[i]);
		i++;
		j++;
	}
}

int count_outside_quotes(int *i, int nbr, char *cmd)
{
	while (cmd[*i] != '\0' && cmd[*i] != '\'' && cmd[*i] != '\"')
	{
		if (*i > 0 && (cmd[*i - 1] == ' ' || cmd[*i - 1] == '	'))
			nbr++;
		(*i)++;
	}
	return (nbr);
}

int count_quotes(char *cmd, char stock, int i)
{
	int nbr;

	nbr = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '	' && cmd[i] != '\'' && cmd[i] != '\"')
			nbr++;
		nbr = count_outside_quotes(&i, nbr, cmd);
		if (cmd[i] == '\0')
			return (nbr);
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			nbr++;
			stock = cmd[i++];
		}
		while(cmd[i] != '\0' && cmd[i] != stock)
			i++;
		if (cmd[i] == '\0')
			return (nbr);
		else if (cmd[i++] == stock)
			stock = '\0';
	}
	return (nbr);
}

char copy_and_increase(char c, int *i, int *y)
{
	(*i)++;
	(*y)++;
	return (c);
}

void copy_outside_quotes(char *cmd, int *i, int *j, t_tprint new)
{
	int tmp;
	int y;

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

int stock_stock(char c, char *stock, int *tmp, int *i)
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

int copy_inside_quotes(char *cmd, t_c *c, char *stock, t_tprint new)
{
	int tmp;
	int y;

	y = 0;
	if (stock_stock(cmd[c->i], stock, &tmp, &c->i))
		return (1);
	while(cmd[c->i] != '\0' && cmd[c->i] != *stock)
		(c->i)++;
	new.tab[c->j] = malloc(sizeof(char) * (c->i - tmp + 2));
	c->i = tmp;
	if (cmd[c->i] == '\'' || cmd[c->i] == '\"')
		new.tab[c->j][y++] = cmd[(c->i)++];
	while(cmd[c->i] != '\0' && cmd[c->i] != *stock)
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

void create_splitted_cmds(char *cmd, t_tprint new)
{
	int i;
	int j;
	t_c c;
	char stock;


	i = 0;
	j = 0;
	stock = '\0';
	while (cmd[i] != '\0')
	{
		while (cmd[i] == ' ' || cmd[i] == '	')
			i++;
		copy_outside_quotes(cmd, &i, &j, new);
		c.i = i;
		c.j = j;
		if (copy_inside_quotes(cmd, &c, &stock, new))
			break ;
		i = c.i;
		j = c.j;
		j++;
	}
	new.tab[j] = NULL;
}

t_tprint split_cmds(char *cmd, int tablen)
{
	t_tprint new;

	new.tab = malloc(sizeof(char *) * (tablen + 1));
	if (new.tab == NULL)
	{
		new.print = NULL;
		return (new);
	}
	new.print = malloc(sizeof(int) * (tablen + 1));
	new.print[0] = tablen;
	create_splitted_cmds(cmd, new);
	return (new);
}

t_tprint split_both_quotes(char *cmd)
{
	int tablen;
	t_tprint splitted;
	int i;
	char stock;

	i = 0;
	stock = '\0';
	tablen = count_quotes(cmd, stock, i);
	splitted = split_cmds(cmd, tablen);
	return (splitted);
}

void trim_single_and_tprint(t_tprint tmp, t_tprint *tp, int i)
{
	tp->tab[i] = ft_strtrim(tmp.tab[i], "\'");
	if (tmp.print[i + 1] == 1)
		tp->print[i + 1] = 3;
	else
		tp->print[i + 1] = 0;
}

void trim_doubles_and_tprint(t_tprint tmp, t_tprint *tp, int i)
{
	tp->tab[i] = ft_strtrim(tmp.tab[i], "\"");
	if (tmp.print[i + 1] == 1)
		tp->print[i + 1] = 4;
	else
		tp->print[i + 1] = 1;
}

void trim_and_tprint_else(t_tprint tmp, t_tprint *tp, int i)
{
	tp->tab[i] = ft_strdup(tmp.tab[i]);
	if (tmp.print[i + 1] == 1)
		tp->print[i + 1] = 5;
	else
		tp->print[i + 1] = 2;
}

void create_tprint(t_tprint tmp, t_tprint tp)
{
	int i;

	i = 0;
	while (tmp.tab[i] != NULL)
	{
		if (tmp.tab[i][0] == '\'' && tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\'')
			trim_single_and_tprint(tmp, &tp, i);
		else if (tmp.tab[i][0] == '\"' 
				&& tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\"')
			trim_doubles_and_tprint(tmp, &tp, i);
		else if (tmp.tab[i][0] == '\"' || tmp.tab[i][0] == '\'' 
			|| tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\"' 
			|| tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\'')
		{
			tp.tab[i] = ft_strdup(tmp.tab[i]);
			tp.print[i + 1] = -1;
		}
		else
			trim_and_tprint_else(tmp, &tp, i);
		i++;
	}
	tp.tab[i] = NULL;
}

// 0 : pour les string avec single quote
// 1 : pour les string avec double quotes
// 2 : pour les string avec aucune quotes
// 3 : pour les string avec single quote et espace après
// 4 : pour les string avec double quotes et espace après
// 5 : pour les tring avec aucune quotes et espace après
// utiliser display_tab_and_int(tp.print, tp.tab); pour afficher les 2
t_tprint parsing_master(char *cmd)
{
	t_tprint tmp;
	t_tprint tp;

	tmp = split_both_quotes(cmd);
	tp.tab = malloc(sizeof(char *) * (tab_len(tmp.tab) + 1));
	tp.print = malloc(sizeof(int) * (tab_len(tmp.tab) + 1));
	tp.print[0] = tab_len(tmp.tab);
	create_tprint(tmp, tp);
	tabfree(tmp.tab);
	free(tmp.print);
	return (tp);
}

void	echo(t_tprint tp, t_tab t)
{
	t_echo elem;
	
	if (tab_len(tp.tab) < 2)
		elem.nbr_args = 0;
	else
		elem = echo_parsing(tp.tab, t, tp.print);
	if (elem.nbr_args == 0 && elem.flag != 'n')
		printf("\n");
	if (elem.nbr_args > 0 && elem.flag == 'n')
		echo_print(elem.args, elem.vars, elem.spaces);
	if (elem.nbr_args > 0 && elem.flag != 'n')
	{
		echo_print(elem.args, elem.vars, elem.spaces);
		printf("\n");
	}
	free_elem(elem);
	exit_status = 0;
}
