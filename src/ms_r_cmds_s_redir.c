/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/09 11:08:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir_next(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		if ((tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
			|| (tab[i][0] == '>' && tab[i][1] == '>'  && ft_strlen(tab[i]) == 2)
			|| (tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
			|| (tab[i][0] == '<' && tab[i][1] == '<'  && ft_strlen(tab[i]) == 2))
				return (1);
		i++;
	}
	return (0);
}

char *find_redir_part(int *i, char **tab)
{
	char *redirstr;
	char *tmp;

	redirstr = ft_strdup("");
	while(tab[*i] != NULL && is_redir_next(&tab[*i - 1]) 
		&& !(tab[*i][0] == '>' && ft_strlen(tab[*i]) == 1)
		&& !(tab[*i][0] == '>' && tab[*i][1] == '>'  && ft_strlen(tab[*i]) == 2)
		&& !(tab[*i][0] == '<' && ft_strlen(tab[*i]) == 1)
		&& !(tab[*i][0] == '<' && tab[*i][1] == '<'  && ft_strlen(tab[*i]) == 2))
	{
		if (*redirstr != '\0')
			tmp = ft_strjoin_sep(redirstr, tab[*i], ' ');
		else
			tmp = ft_strdup(tab[*i]);
		free(redirstr);
		redirstr = tmp;
		(*i)++;
	}
	return (redirstr);
}

char **recreate_cmd(char *cmd, char **tab, int i)
{
	char **new;
	char **ttmp;
	char *newstr;
	char *tmp;
	char *joined;

	new = new_tab();
	while (tab[i] != NULL && is_redir_next(&tab[i]))
	{
		tmp = ft_strjoin_sep(cmd, tab[i], ' ');
		i++;
		newstr = find_redir_part(&i, tab);
		joined = ft_strjoin_sep(tmp, newstr, ' ');
		ttmp = add_to_tab(new, joined);
		free(joined);
		tabfree(new);
		new = ttmp;
		free(tmp);
		free(newstr);
	}
	// ttmp = add_to_tab(new, "");
	// tabfree(new);
	// new = ttmp;
	// new[tab_len(ttmp) - 1] = NULL;
	return (new);
}

// ex : > test1 > test2 echo coucou
// become a tab with 2 char*: > test1 echo coucou, > test2 echo coucou
char **split_w_starting_redir(char **tab)
{
	char **new;
	char *cmd;
	int i;

	i = 0;
	cmd = find_cmd(tab);
	new = recreate_cmd(cmd, tab, i);
	free(cmd);
	return (new);
}