/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:47:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 16:21:55 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tab		t;
	char		*test;
	int			i;

	test = ft_strdup("coucou !les! poulets!!!");
	(void) argc;
	(void) argv;
	t.env = tabdup(envp);
	t.exp = sort_env(envp);
	t.var = new_tab();
	t.token = tokenize(test);
	i = how_many_in_tab(t.token, '!');
	printf("%d\n", i);
	return (0);
}
