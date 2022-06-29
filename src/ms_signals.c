/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:41 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/27 15:10:09 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    on_sigquit(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	//printf ("signal quit ctrl backslash:%d\n",sig);
	if (sig == 3)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void    on_siginit(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	//printf ("signal init ctrl_c:%d\n",sig);
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//gestionnaire de signaux
void    signal_handler(void)
{
	struct sigaction	sia;

	sigemptyset(&sia.sa_mask);
	sia.sa_flags = SA_SIGINFO;
	sia.sa_sigaction = on_sigquit;
	sigaction(SIGQUIT, &sia, NULL);
	sia.sa_sigaction = on_siginit;
	sigaction(SIGINT, &sia, NULL);

	return ;