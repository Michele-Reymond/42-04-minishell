/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/30 22:50:53 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*cmd;
	char		*tmp;
	char		*symbol;
	t_tab		t;

	(void) argv;
	check_args(argc);
	t.env = tabdup(envp);
	t.exp = make_export(t.env);
	t.p.cmds = NULL;
	symbol = NULL;
	signal_handler();
	tmp = readline("🌸 >> ");
	while (tmp != NULL)
	{
		cmd = exit_status_convert(tmp, symbol);
		if (strlen(cmd) > 0)
		{
			add_history(tmp);
			free(tmp);
			monitor(cmd, &t);
		}
		tmp = readline("🌸 >> ");
	}
	exit(g_exit_status);
}

// TO DO
// Verifier toutes les sorties. valeur de exit_status
// Test only spaces or tabs. (comment faire avec TAB?)
// Unset the $PATH and check if it is not working anymore
// signaux
