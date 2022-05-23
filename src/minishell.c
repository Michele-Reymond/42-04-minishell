/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/23 19:59:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// trier env
// lui ajouter les variables de export
// afficher avec export
// export salut > ça créer la variable mais sans valeur



int	main(int argc, char **argv, char **envp)
{
	t_echo	test;

	(void)argc;
	(void)argv;
	sort_env(envp);
	test.cmd = "echo";
	test.nbr_args = 3;
	test.flag = ' ';
	test.vars = NULL;
	test.args = malloc(sizeof(char *) * 4);
	test.args[0] = "bonjour";
	test.args[1] = "les";
	test.args[2] = "copains";
	test.args[3] = NULL;
	echo(test);
}