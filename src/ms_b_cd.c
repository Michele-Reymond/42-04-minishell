/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:16:50 by vroch             #+#    #+#             */
/*   Updated: 2022/06/17 16:24:32 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ms_b_cd_init(char *new,t_tprint tp, t_tab *t)
{
	int			i;
	int			j;
	int			k;

	if (tp.tab[1][0] == '~')
	{
		i = 0;
		while (t->env[i] != NULL)
		{
			if (!ft_strncmp(t->env[i], "HOME", 4))
			{
				j = 5;
				while (t->env[i][j] != '\0')
				{
					new[j-5] = t->env[i][j];
					j++;
				}
				k = 1;
				while (tp.tab[1][k] != '\0')
				{
					new[j-5] = tp.tab[1][k];
					j++;
					k++;
				}
				break;
			}
			i++;
		}
	}
	else
	{
		new = tp.tab[1];
	}
	return (new);
}


/* **************************************************************************
 *  parameter : buf = full line from readline.
 *  buf is going to be separated from "cd " --> param
 *  and re-created in case of :
 *   ~ --> usage of value from variable HOME
 */

t_tab *ms_b_cd(t_tprint tp, t_tab *t)
{

	char		*new;
	t_var 		var;

	new = malloc (200 * sizeof (char));
	new = ms_b_cd_init(new, tp, t);
	
	//printf("%s\n",new);
	if (chdir(new) == -1)
	{
		printf("minishell: cd: %s: ", tp.tab[1]);
		printf(ERROR_FILE);
		exit_status = 1;
	}
	else
	{
		// maj variables d'environnement
		var.key = "OLDPWD";
		var.value = getenv("PWD");
		t->env = update_env(t->env, var, false);
		t->exp = update_env(t->exp, var, false);
		//printf("old var.value %s : %s\n",var.key,var.value);
		var.key = "PWD";
		var.value = getcwd(NULL, 0);
		t->env = update_env(t->env, var, false);
		t->exp = update_env(t->exp, var, false);
		//printf("new var.value %s : %s\n",var.key,var.value);


	}
	free(new);
    return (t);
}
