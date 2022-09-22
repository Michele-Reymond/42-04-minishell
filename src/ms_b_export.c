/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 12:13:57 by mreymond         ###   ########.fr       */
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
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

char	*export_without_spaces(int *i, t_tprint tp)
{
	char	*new;
	char	*joined;
	char	*tmp;

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

char	**parsing_for_export(t_tprint tp)
{
	int		i;
	int		j;
	char	**new;
	int		tablen;

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

void	export_mechanic(int *i, int *j, t_var *vartab, t_tab *t)
{
	if (vartab[*j].status == 0 && !(vartab[*j].key[0] == '_'
			&& ft_strlen(vartab[*j].key) == 1))
		update_with_new_var(t, vartab[*j], i, j);
	else if (!(vartab[*j].key[0] == '_'
			&& ft_strlen(vartab[*j].key) == 1))
		export_errors(vartab[*j], i, j);
	else
		export_increase(i, j);
}

t_tab	*ft_export(t_tab *t, t_tprint tp)
{
	t_var	*vartab;
	char	**token;
	int		i;
	int		j;

	i = 1;
	j = 0;
	vartab = NULL;
	token = parsing_for_export(tp);
	if (tab_len(token) == 1)
		display_export(t->exp);
	else
	{
		vartab = create_vartab(&i, token);
		while (i > 1)
			export_mechanic(&i, &j, vartab, t);
	}
	free_vartab(vartab, tab_len(token) - 1);
	tabfree(token);
	return (t);
}
