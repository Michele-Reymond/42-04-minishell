/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 15:10:52 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tab		t;
	char* 		cmd;

	(void) argc;
	(void) argv;
	t.env = tabdup(envp);
	t.exp = sort_env(envp);
	t.var = new_tab();

	while ((cmd = readline("🌸 >> ")) != NULL) 
	{
		if (strlen(cmd) > 0) 
		{
			add_history(cmd);
			if (!strcmp(cmd, "exit"))
				break;
			launch_builtins(cmd, t);

		}
  	  free(cmd);
	}
	return (0);
}
