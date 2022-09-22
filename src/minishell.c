/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/22 16:53:44 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 * enlever le ctrl-c visible : t.curr.c_lflag &= ~ECHOCTL;
 * pour rendre visisble le ctrl-c : t.curr.c_lflag |= ECHOCTL
 */
static	t_tab	main_termios(t_tab t)
{
	t.p.cmds = NULL;
	tcgetattr(STDIN_FILENO, &t.curr);
	tcgetattr(STDIN_FILENO, &t.save);
	t.curr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &t.curr);
	return (t);
}

static char	*main_readline(char *tmp, char *cmd, t_tab *t)
{
	if (strlen(cmd) > 0)
	{
		add_history(tmp);
		free(tmp);
		monitor(cmd, t);
	}
	tmp = readline("🌸 >> ");
	return (tmp);
}

int	main(int argc, char **argv, char **envp)
{
	char			*cmd;
	char			*tmp;
	char			*symbol;
	t_tab			t;

	(void) argv;
	check_args(argc);
	t.env = tabdup(envp);
	t.exp = make_export(t.env);
	symbol = NULL;
	t = main_termios(t);
	signal_handler();
	tmp = readline(">> ");
	while (tmp != NULL)
	{
		cmd = exit_status_convert(tmp, symbol);
		tmp = main_readline(tmp, cmd, &t);
	}
	tcsetattr(STDIN_FILENO, 0, &t.save);
	exit(g_exit_status);
}
