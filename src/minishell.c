/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/26 17:01:18 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		**stock_env;
	char		**sorted_env;
	t_env_var	new_var;
	t_env_var	new_var2;
	t_echo		test;

	(void) argc;
	(void) argv;
	test.cmd = "echo";
	test.nbr_args = 3;
	test.flag = ' ';
	test.vars = NULL;
	test.args = malloc(sizeof(char *) * 4);
	test.args[0] = "bonjour";
	test.args[1] = "les";
	test.args[2] = "copains";
	test.args[3] = NULL;

	new_var = str_to_var("coucou=bidule");
	new_var2 = str_to_var("frite=patate");
	stock_env = tabdup(envp);
	sorted_env = sort_env(envp);

	// if (ECHO)
		echo(test);
	// else if (CD)
		printf("CD\n");
	// else if (PWD)
		printf("PWD\n");
	// else if (EXPORT)
	// {
		display_export(sorted_env);
		update_env(sorted_env, &new_var);
		sorted_env = update_env(sorted_env, &new_var2);
		printf("_______________________________________\n");
		display_export(sorted_env);
	// }
	// else if (UNSET)
		printf("UNSET TO DO\n");
	// else if (ENV)
	// {
		display_env(stock_env);
	// }
	// else if (EXIT)
		printf("EXIT\n");
	// else
		printf("ERROR\n");
	return (0);
}
