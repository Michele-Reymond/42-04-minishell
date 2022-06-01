/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/01 15:28:18 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tab		t;
	char* 		cmd;
	t_var		first;
	t_var		test;

	(void) argc;
	(void) argv;
	t.env = tabdup(envp);
	t.exp = sort_env(envp);

	// test
	first.key = "FIRST";
	first.value = "0";
	test.key = "test";
	test.value = "Vartest";
	t.var = add_var(new_tab(), first);
	t.var = add_var(t.var, test);
	// fin du test

	while ((cmd = readline("🌸 >> ")) != NULL) 
	{
		t.token = tokenize(cmd);
		if (strlen(cmd) > 0)
		{
			add_history(cmd);
			if (!strcmp(cmd, "exit"))
				break;
			// launch_cmds(cmd, t);
			monitor(cmd, &t);
			// display_tab(t.token);
		}
  	  	free(cmd);
		free(t.token);
	}
	return (0);
}
