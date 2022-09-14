/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:41 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/14 10:22:02 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* **************************************************************************
 *  signal quit ctrl backslash
 */

void	on_sigquit(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == 3)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
/* **************************************************************************
 *  signal init ctrl_c
 */

void	on_sigint(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
/* **************************************************************************
 *  gestionnaire de signauxs
 */

void	signal_handler(void)
{
	struct sigaction	sia;

	sigemptyset(&sia.sa_mask);
	sia.sa_flags = SA_SIGINFO;
	sia.sa_sigaction = on_sigquit;
	sigaction(SIGQUIT, &sia, NULL);
	sia.sa_sigaction = on_sigint;
	sigaction(SIGINT, &sia, NULL);
	return ();
}
