/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 17:40:19 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtins(char *cmd, t_tab t)
{
	(void)	t;

	if (!ft_strncmp(cmd, "cd", 2))
		ms_b_cd(cmd);
	else if (!ft_strncmp(cmd, "pwd", 3))
		ms_b_pwd();
	//else if (!ft_strncmp(cmd, "echo", 4))
	//	echo(args);		
	//else if (!ft_strncmp(buf, "export", 6))
	//	ft_export(tab, var);
	//else if (cmd == UNSET)
	//	remove_var(tab, var);
	//else if (cmd == ENV)
	//	display_tab(tab);
	//else if (cmd == EXIT)
	//	printf("EXIT\n");
	else
		ms_b_other(cmd);
	return(0);
}
