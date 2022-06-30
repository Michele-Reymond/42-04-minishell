/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/30 18:07:58 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char		*cmd;
	char		*tmp;
	t_tab		t;

	(void) argv;
	check_args(argc);
	t.env = tabdup(envp);
	t.exp = make_export(t.env);
	// signal_handler();
	while ((tmp = readline("🌸 >> ")) != NULL)
	{
		cmd = exit_status_convert(tmp);
		if (strlen(cmd) > 0)
		{
			add_history(tmp);
			monitor(cmd, &t);
		}
  	  	free(cmd);
		free(tmp);
	}
	exit(exit_status);
}

// TO DO (Michèle)!!
// 1. launch_pipes_with_redir(p, t) à fair pour le parsing!!!
// 2. checker les erreur bash ci-dessous
// 3. verifier toutes les sorties. valeur de exit_status

// quotes:

// 4. .minishell (checker other correctement)
// 5. regler les bugs
// 6. checker les leaks et les closes de fichiers et les protections de malloc
// 7. cleaner cet enfer

// BUGS : 
// Test only spaces or tabs. (comment faire avec TAB?)
// Execute commands but this time use a relative path (pas bien compris cett demande)
// Unset the $PATH and check if it is not working anymore

// FAUX par rapport a bash :

//1. 
//echo " > << > >>> <<<"     << truc qui sort :
// > << > >>> <<< .heredoc

//2. echo " > << > >>> <<<"     < truc
// dois sortir l'erreur : bash: truc: No such file or directory