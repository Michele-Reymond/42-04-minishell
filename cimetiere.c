// cimetiere des fonctions trop longues qui ont été découpée
// ou des fonctions inutilisées


// void count_redir(t_tprint tp, t_parse *p)
// {
// 	int		i;
// 	int		*nbr1;
// 	int		*nbr2;

// 	i = 0;
// 	p->redir_out = 0;
// 	p->redir_out_d = 0;
// 	p->redir_in = 0;
// 	p->redir_in_d = 0;
// 	while (tp.tab[i] != NULL)
// 	{
// 		if (tp.print[i + 1] == 2 || tp.print[i + 1] == 5)
// 		{
// 			nbr1 = check_redir(tp.tab[i], '>');
// 			if (nbr1[0] == -1 || nbr1[1] == -1)
// 			{
// 				p->redir_out = nbr1[0];
// 				p->redir_out_d = nbr1[1];
// 				if (nbr1)
// 				{
// 					free(nbr1);
// 					nbr1 = NULL;
// 				}
// 				if (nbr2)
// 				{
// 					free(nbr2);
// 					nbr2 = NULL;
// 				}
// 				break ;
// 			}
// 			p->redir_out += nbr1[0];
// 			p->redir_out_d += nbr1[1];
// 			nbr2 = check_redir(tp.tab[i], '<');
// 			if (nbr2[0] == -1 || nbr2[1] == -1)
// 			{
// 				p->redir_in = nbr2[0];
// 				p->redir_in_d = nbr2[1];
// 				if (nbr1)
// 				{
// 					free(nbr1);
// 					nbr1 = NULL;
// 				}
// 				if (nbr2)
// 				{
// 					free(nbr2);
// 					nbr2 = NULL;
// 				}
// 				break ;
// 			}
// 			p->redir_in += nbr2[0];
// 			p->redir_in_d += nbr2[1];
// 			if (nbr1)
// 			{
// 				free(nbr1);
// 				nbr2 = NULL;
// 			}
// 			if (nbr2)
// 			{
// 				free(nbr2);
// 				nbr2 = NULL;
// 			}
// 		}
// 		i++;
// 	}
// 	p->redir = p->redir_in + p->redir_in_d + p->redir_out + p->redir_out_d;
// }

// t_tprint split_pipes_phase_1(t_tprint tp)
// {
// 	int i;
// 	int j;
// 	int k;
// 	char **splitted;
// 	char **tmp;
// 	t_tprint last;
// 	char *quoted;
// 	int pipes;

// 	i = 0;
// 	j = 1;
// 	last.tab = new_tab();
// 	pipes = count_multi_pipes_cmds(tp);
// 	last.print = malloc(sizeof(char *) * (pipes + tp.print[0] + 1));
// 	last.print[0] = pipes + tp.print[0];
// 	while (tp.tab[i] != NULL)
// 	{
// 		if(how_many_in_str(tp.tab[i], '|') > 0 
// 			&& (tp.print[i + 1] == 2 || tp.print[i + 1] == 5) 
// 			&& ft_strlen(tp.tab[i]) > 1)
// 		{
// 			splitted = split_out(tp.tab[i]);
// 			tmp = tabjoin(last.tab, splitted);
// 			k = 0;
// 			while (k < tab_len(splitted) - 1)
// 			{
// 				last.print[j] = 2;
// 				j++;
// 				k++;
// 			}
// 			if (tp.print[i + 1] == 2)
// 				last.print[j] = 2;
// 			else
// 				last.print[j] = 5;
// 			j++;
// 			tabfree(last.tab);
// 			tabfree(splitted);
// 			last.tab = tmp;
// 		}
// 		else
// 		{
// 			if (tp.print[i + 1] == 1 && i != 0)
// 			{
// 				last.print[j] = 1;
// 				quoted = add_quotes(tp.tab[i], '\"');
// 			}
// 			else if (tp.print[i + 1] == 4 && i != 0)
// 			{
// 				last.print[j] = 4;
// 				quoted = add_quotes(tp.tab[i], '\"');
// 			}
// 			else if (tp.print[i + 1] == 0 && i != 0)
// 			{
// 				last.print[j] = 0;
// 				quoted = add_quotes(tp.tab[i], '\'');
// 			}
// 			else if (tp.print[i + 1] == 3 && i != 0)
// 			{
// 				last.print[j] = 3;
// 				quoted = add_quotes(tp.tab[i], '\'');
// 			}
// 			else if (tp.print[i + 1] == 5)
// 			{
// 				last.print[j] = 5;
// 				quoted = ft_strdup(tp.tab[i]);
// 			}
// 			else
// 			{
// 				last.print[j] = 2;
// 				quoted = ft_strdup(tp.tab[i]);
// 			}
// 			tmp = add_to_tab(last.tab, quoted);
// 			tabfree(last.tab);
// 			free(quoted);
// 			quoted = NULL;
// 			last.tab = tmp;
// 			tmp = NULL;
// 			j++;
// 		}
// 		i++;
// 	}
// 	tmp = add_to_tab(last.tab, "");
// 	tabfree(last.tab);
// 	last.tab = tmp;
// 	last.tab[tab_len(tmp) - 1] = NULL;
// 	return (last);
// }

// t_tprint echo_parse_quotes(t_tprint tp)
// {
// 	int i;
// 	t_tprint new;
// 	char **tmp;
// 	char **splitted;
// 	int *intmp;

// 	i = 0;
// 	new.tab = new_tab();
// 	new.print = new_inttab();
// 	while (tp.tab[i] != NULL)
// 	{
// 		if (tp.print[i + 1] == 1 || tp.print[i + 1] == 4)
// 		{
// 			splitted = ft_split_one_space(tp.tab[i]);
// 			tmp = tabjoin(new.tab, splitted);
// 			intmp = fill_inttab(new.print, 1, tab_len(splitted));
// 			tabfree(new.tab);
// 			free(new.print);
// 			free(splitted);
// 			new.print = intmp;
// 			new.tab = tmp;
// 		}
// 		else
// 		{
// 			tmp = add_to_tab(new.tab, tp.tab[i]);
// 			intmp = add_to_inttab(new.print, tp.print[i + 1]);
// 			free(new.print);
// 			new.print = intmp;
// 			tabfree(new.tab);
// 			new.tab = tmp;
// 		}
// 		i++;
// 	}
// 	return (new);
// }

// t_tprint parsing_master(char *cmd)
// {
// 	t_tprint tmp;
// 	t_tprint tp;
// 	int i;

// 	i = 0;
// 	tmp = split_both_quotes(cmd);
// 	tp.tab = malloc(sizeof(char *) * tab_len(tmp.tab) + 1);
// 	tp.print = malloc(sizeof(int) * tab_len(tmp.tab) + 1);
// 	tp.print[0] = tab_len(tmp.tab);
// 	while (tmp.tab[i] != NULL)
// 	{
// 		if (tmp.tab[i][0] == '\'' && tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\'')
// 		{
// 			tp.tab[i] = ft_strtrim(tmp.tab[i], "\'");
// 			if (tmp.print[i + 1] == 1)
// 				tp.print[i + 1] = 3;
// 			else
// 				tp.print[i + 1] = 0;
// 		}
// 		else if (tmp.tab[i][0] == '\"' && tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\"')
// 		{
// 			tp.tab[i] = ft_strtrim(tmp.tab[i], "\"");
// 			if (tmp.print[i + 1] == 1)
// 				tp.print[i + 1] = 4;
// 			else
// 				tp.print[i + 1] = 1;
// 		}
// 		else if (tmp.tab[i][0] == '\"' || tmp.tab[i][0] == '\'' 
// 			|| tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\"' || tmp.tab[i][ft_strlen(tmp.tab[i]) - 1] == '\'')
// 		{
// 			tp.tab[i] = ft_strdup(tmp.tab[i]);
// 			tp.print[i + 1] = -1;
// 		}
// 		else
// 		{
// 			tp.tab[i] = ft_strdup(tmp.tab[i]);
// 			if (tmp.print[i + 1] == 1)
// 				tp.print[i + 1] = 5;
// 			else
// 				tp.print[i + 1] = 2;
// 		}
// 		i++;
// 	}
// 	tp.tab[i] = NULL;
// 	return (tp);
// }

// int copy_single_quote(char **new, char **tab, int j, int i)
// {
// 	new[j] = ft_strdup("\'");
// 	j++;
// 	new[j] = ft_strdup(&tab[i][1]);
// 	return (j);
// }

// char **manage_single_quotes(char **tab)
// {
// 	int i;
// 	int j;
// 	char **new;

// 	i = 0;
// 	j = 0;
// 	printf ("ici\n");
// 	new = malloc(sizeof(char *) * tab_len(tab) + 3);
// 	while (tab[i] != NULL)
// 	{
// 		if (tab[i][0] == '\'')
// 			j = copy_single_quote(new, tab, j, i);
// 		else if (tab[i][ft_strlen(tab[i]) - 1] == '\'')
// 		{
// 			new[j] = ft_strldup(tab[i], ft_strlen(tab[i]));
// 			j++;
// 			new[j] = ft_strdup("\'");
// 		}
// 		else
// 			new[j] = ft_strdup(tab[i]);
// 		i++;
// 		j++;
// 	}
// 	new[j] = NULL;
// 	return (new);
// }

// char **test1(char *str, char **tab)
// {
// 	char **new;
// 	char *strtmp;

// 	strtmp = ft_strtrim(str, "\'");
// 	new = add_to_tab(tab, strtmp);
// 	free(strtmp);
// 	return (new);
// }

// char **test2(char *str)
// {
// 	char **new;
// 	char **tmp;
// 	char **tmp1;
// 	char **tmp3;
// 	char *strtmp;

// 	strtmp = ft_strtrim(str, "\'");
// 	tmp1 = ft_split(strtmp, ' ');
// 	free(strtmp);
// 	tmp = malloc(sizeof(char *) * 2);
// 	tmp[0] = ft_strdup("\'");
// 	tmp[1] = NULL;
// 	tmp3 = tabjoin(tmp, tmp1);
// 	tabfree(tmp);
// 	tabfree(tmp1);
// 	new = add_to_tab(tmp3, "\'");
// 	return (new);
// }

// t_tprint doubles_inside(char *cmd)
// {
// 	char **new;
// 	char **tmp;
// 	char **tmp2;
// 	char **tmp3;
// 	int *printing;
// 	int *inttmp;
// 	int in_d;
// 	t_tprint tp;
// 	int i;
	
// 	i = 0;
// 	in_d = 0;
// 	tmp = ft_split_with_sep(cmd, '\'');
// 	tmp2 = trim_tab(tmp);
// 	tabfree(tmp);
// 	new = new_tab();
// 	printing = new_inttab();
// 	while (tmp2[i] != NULL)
// 	{
// 		if (tmp2[i][0] == '\'' && in_d == 0)
// 		{
// 			tmp = test1(tmp2[i], new);
// 			tabfree(new);
// 			new = tmp;
// 			inttmp = add_to_inttab(printing, 0);
// 			free(printing);
// 			printing = inttmp;
// 		}
// 		else if (tmp2[i][0] == '\'' && in_d == 1)
// 		{
// 			tmp = test2(tmp2[i]);
// 			display_tab(tmp);
// 			tmp3 = tabjoin(new, tmp);
// 			tabfree(new);
// 			new = tmp3;
// 			inttmp = fill_inttab(printing, 1, tab_len(tmp));
// 			free(printing);
// 			printing = inttmp;
// 			tabfree(tmp);
// 		}
// 		else if (how_many_in_str(tmp2[i], '\"') > 0)
// 		{
// 			if (tmp2[i][0] == '\"' && how_many_in_str(tmp2[i], '\"') == 1)
// 				in_d = 1;
// 			else
// 				in_d = 0;
// 			tmp3 = split_quotes(tmp2[i], '\"');
// 			tmp = tabjoin(new, tmp3);
// 			tabfree(new);
// 			new = tmp;
// 			inttmp = fill_inttab(printing, 1, tab_len(tmp3));
// 			free(printing);
// 			printing = inttmp;
// 			tabfree(tmp3);
// 		}
// 		else
// 		{
// 			tmp3 = tokenize(tmp2[i]);
// 			tmp = tabjoin(new, tmp3);
// 			tabfree(new);
// 			new = tmp;
// 			inttmp = fill_inttab(printing, 1, tab_len(tmp3));
// 			free(printing);
// 			printing = inttmp;
// 			tabfree(tmp3);
// 		}
// 		i++;
// 	}
// 	tp.tab = new;
// 	tp.print = printing;
// 	return (tp);
// }

// t_tprint split_cmds(char *cmd, int tablen)
// {
// 	int i;
// 	int j;
// 	int y;
// 	int tmp;
// 	char stock;
// 	t_tprint new;

// 	i = 0;
// 	j = 0;
// 	y = 0;
// 	tmp = 0;
// 	stock = '\0';
// 	new.tab = malloc(sizeof(char *) * (tablen + 1));
// 	if (new.tab == NULL)
// 	{
// 		new.print = NULL;
// 		return (new);
// 	}
// 	new.print = malloc(sizeof(int) * tablen + 1);
// 	new.print[0] = tablen;
// 	while (cmd[i] != '\0')
// 	{
// 		while (cmd[i] == ' ' || cmd[i] == '	')
// 			i++;
// 		while (cmd[i] != '\0' && cmd[i] != '\'' && cmd[i] != '\"')
// 		{
// 			y = 0;
// 			tmp = i;
// 			while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '	' && cmd[i] != '\'' && cmd[i] != '\"')
// 				i++;
// 			if (cmd[i] == ' ' || cmd[i] == '	')
// 				new.print[j + 1] = 1;
// 			else
// 				new.print[j + 1] = 0;
// 			new.tab[j] = malloc(sizeof(char) * (i - tmp + 1));
// 			i = tmp;
// 			while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '	' && cmd[i] != '\'' && cmd[i] != '\"')
// 			{
// 				new.tab[j][y] = cmd[i];
// 				i++;
// 				y++;
// 			}
// 			new.tab[j][y] = '\0';
// 			j++;
// 			if (cmd[i] == ' ' || cmd[i] == '	')
// 				i++;
// 		}
// 		y = 0;
// 		if (cmd[i] == '\0')
// 			break ;
// 		else if (cmd[i] == '\'' || cmd[i] == '\"')
// 		{
// 			stock = cmd[i];
// 			tmp = i;
// 			i++;
// 		}
// 		while(cmd[i] != '\0' && cmd[i] != stock)
// 			i++;
// 		new.tab[j] = malloc(sizeof(char) * (i - tmp + 2));
// 		i = tmp;
// 		if (cmd[i] == '\'' || cmd[i] == '\"')
// 		{
// 			new.tab[j][y] = cmd[i];
// 			i++;
// 			y++;
// 		}
// 		while(cmd[i] != '\0' && cmd[i] != stock)
// 		{
// 			new.tab[j][y] = cmd[i];
// 			i++;
// 			y++;
// 		}
// 		if (cmd[i] == stock)
// 		{
// 			stock = '\0';
// 			new.tab[j][y] = cmd[i];
// 			i++;
// 			y++;
// 		}
// 		if (cmd[i] == ' ' || cmd[i] == '	')
// 			new.print[j + 1] = 1;
// 		else
// 			new.print[j + 1] = 0;
// 		new.tab[j][y] = '\0';
// 		j++;
// 	}
// 	new.tab[j] = NULL;
// 	return (new);
// }

// int check_if_in(char *cmd, char in, char out, int pos)
// {
// 	int *q_out;
// 	int *q_in;
// 	int i;
// 	int j;

// 	i = 1;
// 	j = pos;
// 	q_in = character_pos(cmd, in);
// 	q_out = character_pos(cmd, out);
// 	while (i <= q_out[0])
// 	{
// 		j = pos;
// 		while (j <= q_in[0])
// 		{
// 			if (q_in[j] > q_out[i] && q_in[j] > q_out[i + 1])
// 				return (0);
// 			else if (q_in[j] > q_out[i] && q_in[j] < q_out[i + 1])
// 			{
// 				if (q_in[j + 1] < q_out[i + 1])
// 					return (q_in[j + 1]);
// 				else
// 					return (-1);
// 			}
// 			j += 2;
// 		}
// 		i += 2;
// 	}
// 	return (-2);
// }

// char **seperated_quotes(char *cmd)
// {
// 	char **new;
// 	char **tmp;
// 	char **tmp2;
// 	char **tmp3;
// 	int i;
	
// 	i = 0;
// 	tmp = ft_split(cmd, '\'');
// 	tmp2 = trim_tab(tmp);
// 	tabfree(tmp);
// 	new = new_tab();
// 	while (tmp2[i] != NULL)
// 	{
// 		if (how_many_in_str(tmp2[i], '\"') > 0)
// 		{
// 			tmp3 = split_quotes(tmp2[i], '\"');
// 			tmp = tabjoin(new, tmp3);
// 			tabfree(new);
// 			new = tmp;
// 			tabfree(tmp3);
// 		}
// 		else
// 		{
// 			tmp = add_to_tab(new, tmp2[i]);
// 			tabfree(new);
// 			new = tmp;
// 		}
// 		i++;
// 	}
// 	return (new);
// }

// // trouver les positions d'un caractère dans une string
// // pos[0] correspond au nombre de c qu'il y a
// // à partir de pos[1] cela correspond aux positions du caractère dans la string
// int	*character_pos(char *str, char c)
// {
// 	int i;
// 	int j;
// 	int nbr;
// 	int *pos;

// 	i = 0;
// 	j = 1;
// 	nbr = how_many_in_str(str, c);
// 	pos = malloc(sizeof(int) * nbr + 1);
// 	pos[0] = nbr;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == c)
// 		{
// 			pos[j] = i;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (pos);
// }

// char **split_quotes(char *cmd, char quote)
// {
// 	char **new;
// 	char **tmp;
// 	char **tmp2;
// 	char *tmpstr;

// 	if (quote == '\'')
// 	{
// 		tmp = ft_split(cmd, quote);
// 		new = trim_tab(tmp);
// 	}
// 	else
// 	{
// 		tmp = ft_split(cmd, quote);
// 		tmp2 = trim_tab(tmp);
// 		tmpstr = tab_to_str(tmp2);
// 		tabfree(tmp2);
// 		new = ft_split_one_space(tmpstr);
// 		free(tmpstr);
// 	}
// 	tabfree(tmp);
// 	return (new);
// }

// // enlever les espaces et tab des tableaux
// char **trim_tab(char **tab)
// {
// 	char **new;
// 	char *tmp;
// 	int len;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	while (tab[i] != NULL)
// 	{
// 		if (!(how_many_in_str(tab[i], ' ') + how_many_in_str(tab[i], '	') == (int)ft_strlen(tab[i])))
// 			len++;
// 		i++;
// 	}
// 	i = 0;
// 	new = malloc(sizeof(char *) * (len + 1));
// 	tmp = malloc(sizeof(char *) * (tab_len(tab) + 1));
// 	while (tab[i] != NULL)
// 	{
// 		tmp = ft_strtrim(tab[i], " 	");
// 		if (*tmp != '\0')
// 		{
// 			new[j] = ft_strtrim(tab[i], " 	");
// 			j++;
// 		}
// 		free(tmp);
// 		i++;
// 	}
// 	new[j] = NULL;
// 	return (new);
// }

// int count_quotes(char *cmd)
// {
// 	int i;
// 	char stock;
// 	int nbr;

// 	i = 0;
// 	nbr = 0;
// 	stock = '\0';
// 	while (cmd[i] != '\0')
// 	{
// 		if (cmd[i] != ' ' && cmd[i] != '	' && cmd[i] != '\'' && cmd[i] != '\"')
// 			nbr++;
// 		while (cmd[i] != '\0' && cmd[i] != '\'' && cmd[i] != '\"')
// 		{
// 			if (cmd[i - 1] == ' ' || cmd[i - 1] == '	')
// 				nbr++;
// 			i++;
// 		}
// 		if (cmd[i] == '\0')
// 			return (nbr);
// 		else if (cmd[i] == '\'' || cmd[i] == '\"')
// 		{
// 			nbr++;
// 			stock = cmd[i++];
// 		}
// 		while(cmd[i] != '\0' && cmd[i] != stock)
// 			i++;
// 		if (cmd[i] == '\0')
// 			return (nbr);
// 		else if (cmd[i++] == stock)
// 			stock = '\0';
// 	}
// 	return (nbr);
// }