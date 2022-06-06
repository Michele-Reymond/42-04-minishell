/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:16:50 by vroch             #+#    #+#             */
/*   Updated: 2022/05/27 17:36:24 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* **************************************************************************
 *  parameter : buf = full line from readline.
 *  buf is going to be separated from "cd " --> param
 *  and re-created in case of :
 *   ~ --> usage of value from variable HOME
 *  structur returned 
 */

static t_ms_b_cd	ms_b_cd_init(char *buf)
{
	t_ms_b_cd	str;
	int			i;
	int			j;	

	str.home = getenv("HOME");
	str.len = ft_strlen(buf) + ft_strlen(str.home);
	str.param = malloc(str.len * sizeof(char));
	i = 0;
	while (i < str.len)
		str.param[i++] = '\0';
	i = 3;
	j = 0;
	if (buf[i] == '~')
	{
		while (str.home[j] != '\0')
		{
			str.param[j] = str.home[j];
			j++;
		}
		i = 4;
	}
	str.pos_buf = i;
	str.pos_param = j;
	return (str);
}
/* **************************************************************************
 *  parameter : buf = full line from readline.
 *  buf is going to be separated from "cd " --> param
 *  and re-created in case of :
 *   ~ --> usage of value from variable HOME
 */

t_tab *ms_b_cd(char *buf, t_tab *t)
{
	t_ms_b_cd	str;
	int			i;
	int			j;
	t_var 		var;

	str = ms_b_cd_init(buf);
	i = str.pos_buf;
	j = str.pos_param;
	while (buf[i] != '\0')
	{
		str.param [j] = buf[i];
		i++;
		j++;
	}	
	if (chdir(str.param) == -1)
		ft_putendl_fd("no such file or directory", 2);
	else
	{
		// maj variables d'environnement
		var.key = "OLDPWD";
		var.value = getenv("PWD");
		update_env(t->env, var);
		printf("old var.value %s : %s",var.key,var.value);
		var.key = "PWD";
		var.value = str.param;
		update_env(t->env, var);
		printf("new var.value %s : %s",var.key,var.value);

	}
	free(str.param);
    return (t);
}
