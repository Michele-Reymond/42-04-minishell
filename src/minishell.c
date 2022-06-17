/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/17 16:23:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char* 		cmd;
	t_tab		t;
	// t_var		first;
	// t_var		test;

	(void) argv;
	check_args(argc);
	t.env = tabdup(envp);
	t.exp = make_export(t.env);
	while ((cmd = readline("🌸 >> ")) != NULL) 
	{
		t.token = tokenize(cmd);
		if (strlen(cmd) > 0)
		{
			add_history(cmd);
			if (!ft_strncmp(cmd, "exit", 4) && (cmd[4] == ' ' || cmd[4] == '\0'))
				break ;
			monitor(cmd, &t);
		}
  	  	free(cmd);
		printf("exit status is %d\n", exit_status);
		// free(t.token);
	}
	exit(exit_status);
}


	// test
	// first.key = "FIRST";
	// first.value = "0";
	// test.key = "test";
	// test.value = "Vartest";
	// t.var = add_var(new_tab(), first);
	// t.var = add_var(t.var, test);
	// fin du test