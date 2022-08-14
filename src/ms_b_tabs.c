/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:26:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/13 22:35:51 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	tabfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

char	**tabdup(char **tab)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(tab) + 1));
	if (new == NULL)
		return (NULL);
	while (tab[i] != NULL)
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**new_tab(void)
{
	char	**new;

	new = malloc(sizeof(char *) * 1);
	new[0] = NULL;
	return (new);
}

void	display_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}


// displaying all vars exept variable without value
void	display_env(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strchr(tab[i], '=') != NULL)
			// if specific to VR. - remove for normal usage
			//if(!ft_strncmp(tab[i],"PWD",3) || !ft_strncmp(tab[i],"OLDPWD",6)) 		
			printf("%s\n", tab[i]);
		i++;
	}
}

char	*tab_to_str(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup("");
	while (tab[i++] != NULL)
	{
		if (*tab[i] == '\0')
		{
			str = ft_strjoin(tmp, " ");
			free(tmp);
			tmp = str;
		}
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free(tmp);
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free(tmp);
			tmp = str;
		}
	}
	return (str);
}
