/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/24 15:03:41 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour le parsing voir l'onglet parsing de Notion

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	sort_caps(char **env, char **sorted)
{
	char	alphabet;
	int		i;
	int		j;

	alphabet = 'A';
	j = -1;
	while (alphabet != 'Z')
	{
		i = -1;
		while (env[++i])
		{
			if (env[i][0] == alphabet)
				sorted[++j] = ft_strdup(env[i]);
		}
		alphabet++;
	}
	return (j);
}

void	sort_small(char **env, char **sorted, int j)
{
	char	alphabet;
	int		i;

	i = -1;
	alphabet = 'a';
	while (alphabet != 'z')
	{
		i = -1;
		while (env[++i])
		{
			if (env[i][0] == alphabet)
				sorted[++j] = ft_strdup(env[i]);
		}
		alphabet++;
	}
}

char	**sort_env(char **env)
{
	char	alphabet;
	char	**sorted;
	int		i;
	int		j;

	j = -1;
	alphabet = 'A';
	sorted = malloc(sizeof(char *) * tab_len(env));
	j = sort_caps(env, sorted);
	i = -1;
	while (env[++i])
	{
		if (!(env[i][0] >= 'A' && env[i][0] <= 'Z')
				&& !(env[i][0] >= 'a' && env[i][0] <= 'z'))
			sorted[++j] = ft_strdup(env[i]);
	}
	sort_small(env, sorted, j);
	return (sorted);
}

void	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

char	**update_env(char **old, char *var)
{
	char	**new;

}

// void	ft_export(char **env, t_env_var new_var)
// {
// 	char	**new_env;

// 	if (new_var.key == NULL)
// 		new_env = sort_env(env);
// 	display_env(new_env);
// }

t_env_var	str_to_var(char *str)
{
	t_env_var	new_var;
	int			i;

	i = 0;
	new_var.key = NULL;
	new_var.value = NULL;
	if (!str || !(ft_isalpha(str[i]) != 0 || str[i] == '_'))
		return (new_var);
	while (str[i] && str[i] != '=' && (ft_isalnum(str[i]) != 0 || str[i] == '_'))
		i++;
	if (str[i] != '=')
		return (new_var);
	new_var.key = malloc(sizeof(char) * i + 1);
	ft_strlcpy(new_var.key, str, i + 1);
	i++;
	new_var.value = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	ft_strlcpy(new_var.value, &str[i], (ft_strlen(str) - i + 1));
	return (new_var);
}

// trier env
// lui ajouter les variables de export
// afficher avec export
// export salut > ça créer la variable mais sans valeur

// 1. Au debut de programme stocker env dans un tableau
// 2. sort le tableau

// 3. si que export: afficher le tableau
// 4. si export + variable
//	4.0 parser la variable
//	4.1 verifier si la variable existe deja
//	4.2 update la variable
//	4.3 sinon ajouter la variable

// !!! echo doit aller chercher dans les variables qui sont dans env (evec export) et dans les variables stockees localement

// _
// commence par u