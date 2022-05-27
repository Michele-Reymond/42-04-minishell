/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 13:26:52 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tab		t;

	(void) argc;
	(void) argv;
	t.env = tabdup(envp);
	t.exp = sort_env(envp);
	t.var = new_tab();
	return (0);
}
