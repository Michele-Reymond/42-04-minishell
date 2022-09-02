/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 15:41:49 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	dup_redir(t_redir r)
{
	t_redir	new;

	new.index = r.index;
	new.dest = ft_strdup(r.dest);
	new.redir = ft_strdup(r.redir);
	new.cmd = ft_strdup(r.cmd);
	return (new);
}

char	*find_cmd(char **tab)
{
	char	*cmd;
	char	*tmp;
	char	**next;
	int		i;

	i = 0;
	next = tab;
	while (is_redir_next(next) && next != NULL)
		next++;
	if (next != NULL)
		next++;
	cmd = ft_strdup("");
	while (next[i] != NULL)
	{
		tmp = join_cmd(cmd, next[i]);
		free(cmd);
		cmd = tmp;
		i++;
	}
	return (cmd);
}

char	*join_cmd(char *cmd, char *next)
{
	char	*tmp;
	char	*joined;

	if (*cmd != '\0')
		tmp = ft_strjoin(cmd, " ");
	else
		tmp = ft_strdup(cmd);
	joined = ft_strjoin(tmp, next);
	free(tmp);
	return (joined);
}

size_t	ft_len_s(char const *s1, char const *s2)
{
	size_t	len;

	len = (ft_strlen(s1) + ft_strlen(s2));
	if ((ft_strlen(s1) == 0) || (ft_strlen(s2) == 0))
		len = len - 1;
	return (len);
}

char	*ft_strjoin_sep(char const *s1, char const *s2, char sep)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	ptr = malloc (sizeof(char) * (ft_len_s(s1, s2) + 2));
	if (ptr == NULL)
		return (NULL);
	while (i < (ft_strlen(s1) + ft_strlen(s2) + 1))
	{
		if (i <= ft_strlen(s1))
			ptr[i] = s1[j++];
		if (i == ft_strlen(s1))
			ptr[i] = sep;
		if (i > ft_strlen(s1))
			ptr[i] = s2[k++];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
