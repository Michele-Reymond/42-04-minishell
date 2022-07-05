/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/07/05 14:34:43 by mreymond         ###   ########.fr       */
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
		if(!ft_strncmp(env[i],"PWD",3) || !ft_strncmp(env[i],"OLDPWD",6)) 
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
int equal_count(t_tprint tp)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	display_tab_and_int(tp.print, tp.tab);
	exit(0);
	while (tp.tab[i] != NULL)
	{
		while (tp.tab[i] != NULL && how_many_in_str(tp.tab[i], '=') == 0)
			i++;
		nbr += i;
		if (tp.tab[i] != NULL && tp.tab[i][ft_strlen(tp.tab[i]) - 1] == '=' && tp.print[i + 1] < 3)
		{

			i++;
		}
		nbr += i;
		i = nbr;
		i++;
	}
	return (0);
}

char **parsing_for_export(t_tprint tp)
{
	int i;

	i = 0;
	equal_count(tp);
	while (tp.tab[i])
	{

		i++;
	}
	return (tp.tab);
}

t_tab	*ft_export(t_tab *t, t_tprint tp)
{
	t_var	*vartab;
	char	**tmp;
	char	**tmp2;
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
		vartab = malloc(sizeof(t_var) * tab_len(token) - 1);
		while (token[i])
		{
			vartab[j] = str_to_var(token[i]);
			if (vartab[j].key == NULL || check_identifier(vartab[j].key))
			{
				vartab[j].key = ft_strdup(token[i]);
				vartab[j].status = -1;
			}
			else if (var_check(vartab[j]))
				vartab[j].status = -1;
			else
				vartab[j].status = 0;
			i++;
			j++;
		}
		j = 0;
		while (i > 1)
		{
			if (vartab[j].status == 0 && !(vartab[j].key[0] == '_' && ft_strlen(vartab[j].key) == 1))
			{
				tmp = update_env(t->env, vartab[j], false);
				tmp2 = update_env(t->exp, vartab[j], true);
				tabfree(t->env);
				tabfree(t->exp);
				t->env = tmp;
				t->exp = tabsort(tmp2);
				exit_status = 0;
				j++;
				i--;
			}
			else if (!(vartab[j].key[0] == '_' && ft_strlen(vartab[j].key) == 1))
			{
				printf(MINISHELL ERRORS_EXP "\'%s\': ", vartab[j].key);
				printf(ERRORS_IDENTIFIER);
				exit_status = 1;
				j++;
				i--;
			}
			else
			{
				j++;
				i--;
				exit_status = 0;
			}
		}
	}
	return (t);
}
