/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/26 16:30:05 by mreymond         ###   ########.fr       */
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
	char	**sorted;
	int		i;
	int		j;

	j = -1;
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

void	display_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	var_exist(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (0);
}

char *var_to_str(t_env_var *var)
{
	char *varstr;
	char *tmp;

	tmp = ft_strjoin("=", var->value);
	varstr = ft_strjoin(var->key, tmp);
	free(tmp);
	return (varstr);
}

char **update_var(char **old, t_env_var *var, int pos)
{
	char *tmp;

	tmp = old[pos];
	old[pos] = var_to_str(var);
	free(tmp);
	return (old);
}

char	**tabdup(char **tab)
{
	char **new;
	int i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(tab) + 1));
	while (tab[i])
	{
		new[i] = strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return(new);
}


char	**add_var(char **old, t_env_var *var)
{
	char **new;
	int i;

	i = 0;
	new = malloc(sizeof(char *) * (tab_len(old) + 2));
	while (old[i])
	{
		new[i] = strdup(old[i]);
		i++;
	}
	new[i] = var_to_str(var);
	i++;
	new[i] = NULL;
	i = 0;
	while(old[i])
	{
		free(old[i]);
		i++;
	}
	free(old);
	return(new);
}

char	**update_env(char **old, t_env_var *var)
{
	char	**new;
	int		var_pos;

	if (var->key == NULL)
		return (old);
	var_pos = var_exist(old, var->key);
	if (var_pos != 0)
		new = update_var(old, var, var_pos);
	else
		new = add_var(old, var);
	return (new);
}

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