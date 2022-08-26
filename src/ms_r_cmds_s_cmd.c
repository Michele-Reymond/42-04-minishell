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

char *find_cmd_sc(char **tab, int *i)
{
	char *cmd;
	char *tmp;

	cmd = ft_strdup("");
	while(tab[*i] != NULL && !(tab[*i][0] == '>' && ft_strlen(tab[*i]) == 1)
		&& !(tab[*i][0] == '>' && tab[*i][1] == '>'  
		&& ft_strlen(tab[*i]) == 2)
		&& !(tab[*i][0] == '<' && ft_strlen(tab[*i]) == 1)
		&& !(tab[*i][0] == '<' && tab[*i][1] == '<'  
		&& ft_strlen(tab[*i]) == 2))
	{
		if (*cmd != '\0')
			tmp = ft_strjoin(cmd, " ");
		else
			tmp = ft_strdup(cmd);
		free(cmd);
		cmd = ft_strjoin(tmp, tab[*i]);
		free(tmp);
		(*i)++;
	}
	return (cmd);
}

char *find_redir_part_sc(int *i, char **tab)
{
	char *redirstr;
	char *tmp;

	redirstr = ft_strdup("");
	while(tab[*i] != NULL && !(tab[*i][0] == '>' && ft_strlen(tab[*i]) == 1)
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

char **recreate_cmd_sc(char *cmd, char **tab, int i)
{
	char **new;
	char **ttmp;
	char *newstr;
	char *tmp;
	char *joined;

	new = new_tab();
	while (tab[i] != NULL)
	{
		tmp = ft_strjoin_sep(cmd, tab[i], ' ');
		i++;
		newstr = find_redir_part_sc(&i, tab);
		joined = ft_strjoin_sep(tmp, newstr, ' ');
		ttmp = add_to_tab(new, joined);
		ft_free(joined);
		tabfree(new);
		new = ttmp;
		ft_free(tmp);
		ft_free(newstr);
	}
	// ttmp = add_to_tab(new, "");
	// tabfree(new);
	// new = ttmp;
	// new[tab_len(ttmp) - 1] = NULL;
	return (new);
}

char **split_w_starting_cmd(char **tab)
{
	char **new;
	char *cmd;
	int i;

	i = 0;
	cmd = find_cmd_sc(tab, &i);
	new = recreate_cmd_sc(cmd, tab, i);
	free(cmd);
	return (new);
}