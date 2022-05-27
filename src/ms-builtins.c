/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 13:40:46 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtins(char *cmd, char **tab, t_var *var, t_echo args)
{
	if (cmd == ECHO)
		echo(args);
	else if (cmd == CD)
		// ms_b_cd(char *buf);
	else if (cmd == PWD)
		//
	else if (cmd == EXPORT)
		ft_export(tab, var);
	else if (cmd == UNSET)
		remove_var(tab, var);
	else if (cmd == ENV)
		display_tab(tab);
	else if (cmd == EXIT)
		printf("EXIT\n");
	else
		printf("ERROR\n");
}
