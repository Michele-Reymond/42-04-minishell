/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:41 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/20 17:04:33 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_kill(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   return;
//    exit(exit_status);
}

//gestionnaire de signaux
void    signal_handler(void)
{
    signal(SIGINT, sig_kill);
    fflush(stdout);
    // kill();
    return ;
}