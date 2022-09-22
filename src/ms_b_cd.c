/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:16:50 by vroch             #+#    #+#             */
/*   Updated: 2022/09/22 16:21:21 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_b_cd_init_tild(char *new, t_tprint tp, t_tab *t, int i)
{
	int			j;
	int			k;

	while (t->env[i] != NULL)
	{
		if (!ft_strncmp(t->env[i], "HOME", 4))
		{
			j = 5;
			while (t->env[i][j] != '\0')
			{
				new[j - 5] = t->env[i][j];
				j++;
			}
			k = 1;
			while (tp.tab[1][k] != '\0')
			{
				new[j - 5] = tp.tab[1][k];
				j++;
				k++;
			}
			break ;
		}
		i++;
	}
	return (new);
}

static char	*ms_b_cd_init(char *new, t_tprint tp, t_tab *t)
{
	int			i;

	i = 0;
	if (tp.tab[1][0] == '~')
	{
		new = ms_b_cd_init_tild(new, tp, t, i);
	}
	else
	{
		new = tp.tab[1];
	}
	return (new);
}

static char	*ms_getenv(t_tab *t, char *vgetenv)
{
	int		len;
	int		i;
	int		j;
	char	*value;

	value = ft_calloc(200, 1);
	len = ft_strlen(vgetenv);
	i = 0;
	while (t->env[i] != NULL)
	{
		if (!ft_strncmp(t->env[i], vgetenv, len))
		{
			j = len + 1;
			while (t->env[i][j] != '\0')
			{
				value[j - (len + 1)] = t->env[i][j];
				j++;
			}
			vgetenv = value;
			break ;
		}
		i++;
	}
	free(value);
	return (vgetenv);
}

/* **************************************************************************
 *  parameter : buf = full line from readline.
 *  buf is going to be separated from "cd " --> param
 *  and re-created in case of :
 *   ~ --> usage of value from variable HOME
 */

t_tab	*ms_b_cd(t_tprint tp, t_tab *t)
{
	char		*new;
	t_var		var;
	char		*vgetenv;

	new = calloc (4, 200);
	new = ms_b_cd_init(new, tp, t);
	if (chdir(new) <= 0)
	{
		printf("minishell: cd: %s: ", tp.tab[1]);
		printf(ERROR_FILE);
		g_exit_status = 1;
	}
	else 
	{
		var.key = "OLDPWD";
		vgetenv = "PWD";
		var.value = ms_getenv(t, vgetenv);
		t->env = update_env(t->env, var, false);
		t->exp = update_env(t->exp, var, false);
		var.key = "PWD";
		var.value = getcwd(NULL, 0);
		t->env = update_env(t->env, var, false);
		t->exp = update_env(t->exp, var, false);
	}
	return (t);
}
