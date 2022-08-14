/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/13 09:57:30 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour le parsing voir l'onglet parsing de Notion

void	display_export(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		// if specific to VR. - remove for normal us
		// if(!ft_strncmp(env[i],"PWD",3) || !ft_strncmp(env[i],"OLDPWD",6)) 
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

char	**update_env(char **old, t_var var, bool quotes)
{
	char	**new;
	int		var_pos;

	if (var.key == NULL)
		return (old);
	var_pos = var_exist(old, var.key);
	if (var_pos != 0)
		new = update_var(old, var, var_pos, quotes);
	else
		new = add_var(old, var, quotes);
	return (new);
}

int var_check(t_var var)
{
	if (!(ft_isalpha(var.key[0]) || var.key[0] == '_'))
		return (1);
	return (0);
}

int check_identifier(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(((ft_isalpha(str[i]) && i == 0) || str[i] == '_' || str[i] == '=') 
				|| ((ft_isalnum(str[i]) && i > 0) || str[i] == '_' || str[i] == '=')))
			return (1);
		i++;
	}
	return (0);
}

// compter les commandes pour export
int spaces_count(t_tprint tp)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] > 2)
			nbr++;
		else
		{
			nbr++;
			while (tp.tab[i] != NULL && tp.print[i + 1] < 3)
				i++;
		}
		if (tp.tab[i] != NULL)
			i++;
	}
	return (nbr);
}

char *export_without_spaces(int *i, t_tprint tp)
{
	char *new;
	char *joined;
	char *tmp;

	joined = ft_strdup(tp.tab[*i]);
	(*i)++;
	while (tp.tab[*i] != NULL && tp.print[*i] < 3)
	{
		tmp = ft_strjoin(joined, tp.tab[*i]);
		free(joined);
		joined = tmp;
		(*i)++;
	}
	new = ft_strdup(joined);
	free(joined);
	return (new);
}

char **parsing_for_export(t_tprint tp)
{
	int i;
	int j;
	char **new;
	int tablen;

	i = 0;
	j = 0;
	tablen = spaces_count(tp);
	new = malloc(sizeof(char *) * (tablen + 1));
	while (tp.tab[i] != NULL)
	{
		if (tp.print[i + 1] < 3)
		{
			new[j] = export_without_spaces(&i, tp);
			j++;
		}
		else
			new[j++] = ft_strdup(tp.tab[i++]);
	}
	new[j] = NULL;
	return (new);
}

t_var *create_vartab(int *i, char **token)
{
	t_var	*vartab;
	int j;

	j = 0;
	vartab = malloc(sizeof(t_var) * (tab_len(token) - 1));
	while (token[*i])
	{
		vartab[j] = str_to_var(token[*i]);
		if (vartab[j].key == NULL || check_identifier(vartab[j].key))
		{
			vartab[j].key = ft_strdup(token[*i]);
			vartab[j].status = -1;
		}
		else if (var_check(vartab[j]))
			vartab[j].status = -1;
		else
			vartab[j].status = 0;
		(*i)++;
		j++;
	}
	return (vartab);
}

void update_with_new_var(t_tab *t, t_var var, int *i, int *j)
{
	char	**tmp;
	char	**tmp2;

	tmp = update_env(t->env, var, false);
	tmp2 = update_env(t->exp, var, true);
	tabfree(t->env);
	tabfree(t->exp);
	t->env = tmp;
	t->exp = tabsort(tmp2);
	exit_status = 0;
	tabfree(tmp2);
	(*j)++;
	(*i)--;
}

void export_errors(t_var var, int *i, int *j)
{
	printf(MINISHELL ERRORS_EXP "\'%s\': ", var.key);
	printf(ERRORS_IDENTIFIER);
	exit_status = 1;
	(*j)++;
	(*i)--;
}

void export_increase(int *i, int *j)
{
	(*j)++;
	(*i)--;
	exit_status = 0;
}

t_tab	*ft_export(t_tab *t, t_tprint tp)
{
	t_var	*vartab;
	char	**token;
	int		i;
	int		j;

	i = 1;
	j = 0;
	token = parsing_for_export(tp);
	if (tab_len(token) == 1)
		display_export(t->exp);
	else
	{
		vartab = create_vartab(&i, token);
		while (i > 1)
		{
			if (vartab[j].status == 0 && !(vartab[j].key[0] == '_' 
					&& ft_strlen(vartab[j].key) == 1))
				update_with_new_var(t, vartab[j], &i, &j);
			else if (!(vartab[j].key[0] == '_' && ft_strlen(vartab[j].key) == 1))
				export_errors(vartab[j], &i, &j);
			else
				export_increase(&i, &j);
		}
	}
	free_vartab(vartab, tab_len(token) - 1);
	tabfree(token);
	return (t);
}

t_tab	*unset(t_tab *t, t_tprint tp)
{
	char	**parsed;
	t_tab	*new_t;

	parsed = parsing_for_export(tp);
	new_t = unset_var(t, parsed);
	tabfree(parsed);
	return (new_t);
}
