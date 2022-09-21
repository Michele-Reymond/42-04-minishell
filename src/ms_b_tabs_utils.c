/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_tabs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:26:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/20 19:38:10 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("%s\n", tab[i]);
		i++;
	}
}

char	**tabjoin(char **tab1, char **tab2)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = tab_len(tab1) + tab_len(tab2);
	new = malloc(sizeof(char *) * (len + 1));
	while (tab1[i] != NULL)
	{
		new[i] = ft_strdup(tab1[i]);
		i++;
	}
	while (tab2[j] != NULL)
	{
		new[i] = ft_strdup(tab2[j]);
		i++;
		j++;
	}
	new[i] = NULL;
	return (new);
}

char	**add_to_tab(char **oldtab, char *str_to_add)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(oldtab) + 2));
	while (oldtab[i] != NULL)
	{
		new[i] = ft_strdup(oldtab[i]);
		i++;
	}
	new[i] = ft_strdup(str_to_add);
	i++;
	new[i] = NULL;
	return (new);
}

char	**add_to_tab_begin(char **oldtab, char *str_to_add)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (tab_len(oldtab) + 2));
	new[i] = ft_strdup(str_to_add);
	i++;
	while (oldtab[j] != NULL)
	{
		new[i] = ft_strdup(oldtab[j]);
		i++;
		j++;
	}
	new[i] = NULL;
	return (new);
}
