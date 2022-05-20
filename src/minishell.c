/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/20 17:22:30 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_echo	test;

	(void)argc;
	(void)argv;
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
