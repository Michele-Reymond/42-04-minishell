/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/27 19:59:50 by mreymond         ###   ########.fr       */
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
	signal_handler();
	while ((tmp = readline("🌸 >> ")) != NULL) 
	{
		cmd = exit_status_convert(tmp);
		if (strlen(cmd) > 0)
		{
			add_history(cmd);
			monitor(cmd, &t);
		}
  	  	free(cmd);
		free(tmp);
	}
	exit(exit_status);
}

// TO DO!!

// quotes :
// echo_print(char **args, char **var, int *print) en cours pas encore ok
// quand il y a des pipes et autres symbols
// // minishell: "echo": Command not found
// echo coucou$coucou qui ne prends pas la variable!!
// segfault de echo 'aled "aled" aled " $coucou" aled aled' 'coucou' "hello '$yeah yo $youhou pouet' machin" "chose"

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