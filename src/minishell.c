/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/24 14:59:08 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		**stock_env;
	t_env_var	new_var;

	(void) argc;
	(void) argv;
	stock_env = sort_env(envp);
	new_var = str_to_var("hello=coucou");
	printf("hello");
	// if("export")
	// 	display_env(stock_env);
	// if ("export et variable")
		update_env(stock_env, new_var);
}
