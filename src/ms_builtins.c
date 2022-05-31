/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:06:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/30 16:04:15 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int monitor(char *cmd, t_tab t)
{
	int pipes;
	int redirections;
	int doublesquotes;
	int quotes;
	
	pipes = how_many_in_str(cmd, '|');
	redirections = how_many_in_str(cmd, '<');
	doublesquotes = how_many_in_str(cmd, '\"');
	quotes = how_many_in_str(cmd, '\'');
	if (pipes == 0 && redirections == 0 && doublesquotes == 0 && quotes == 0)
		launch_builtins(cmd, t);
	return (0);
}

int	launch_builtins(char *cmd, t_tab t)
{
	if (!ft_strncmp(cmd, "cd", 2))
		ms_b_cd(cmd);
	else if (!ft_strncmp(cmd, "pwd", 3))
		ms_b_pwd();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo(t.token, t);
	// else if (!ft_strncmp(buf, "export", 6))
	// 	ft_export(tab, var);
	// else if (cmd == UNSET)
	// 	remove_var(tab, var);
	else if (!ft_strncmp(cmd, "env", 3))
		display_tab(t.env);
	else
		ms_b_other(cmd);
	return(0);
}
