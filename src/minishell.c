/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/20 16:49:02 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char		*cmd;
	char		*tmp;
	t_tab		t;
	// t_var		first;
	// t_var		test;

	(void) argv;
	check_args(argc);
	t.env = tabdup(envp);
	t.exp = make_export(t.env);
	signal_handler();
	while ((tmp = readline("🌸 >> ")) != NULL) 
	{
		t.token = tokenize(tmp);
		cmd = replace_exit_status(t.token);
		if (strlen(cmd) > 0)
		{
			add_history(cmd);
			monitor(cmd, &t);
		}
  	  	free(cmd);
		free(tmp);
		// free(t.token);
	}
	exit(exit_status);
}

// TO DO!!

// 3. signaux
// 4. .minishell (checker other correctement)
// 5. regler les bugs
// 6. checker les leaks et les closes de fichiers et les protections de malloc
// 7. cleaner cet enfer

// BUGS : 
// export foo = bar qui segfault (gestion des erreurs de export)
// printer un $ normal dans echo?
// lancer une commande avec le chemin: /bin/ls
// Test only spaces or tabs. (comment faire avec TAB?)
// Double Quotes :  echo "cat lol.c | cat > lol.c"
// echo '$USER' must print $USER
// Execute commands but this time use a relative path (pas bien compris cett demande)
// Unset the $PATH and check if it is not working anymore



	// test
	// first.key = "FIRST";
	// first.value = "0";
	// test.key = "test";
	// test.value = "Vartest";
	// t.var = add_var(new_tab(), first);
	// t.var = add_var(t.var, test);
	// fin du test