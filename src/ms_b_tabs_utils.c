/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_tabs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:26:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/14 10:15:35 by vroch            ###   ########.fr       */
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
