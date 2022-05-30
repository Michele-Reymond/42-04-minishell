/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-b-export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:43:17 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 13:04:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour le parsing voir l'onglet parsing de Notion

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

char	**update_env(char **old, t_var *var)
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

void	ft_export(char **env, t_var *var)
{
	if (var->key == NULL)
		display_export(env);
	else
		update_env(env, var);
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