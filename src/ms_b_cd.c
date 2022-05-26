/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:16:50 by vroch             #+#    #+#             */
/*   Updated: 2022/05/20 16:51:44 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* **************************************************************************
 *  parameter : arg = full line from readline.
 *  buf is going to be separated from "cd " --> param
 *  and re-created in case of :
 *   ~ --> usage of value from variable HOME
 */
int ms_b_cd(char *buf)
{
	char	*param;
	char	*home;
	int		len;
	int		i;
	int		j;

	home = getenv("HOME");
	len = ft_strlen(buf) + ft_strlen(home);
	param = malloc(len * sizeof(char));
	i = 0;
	while (i < len)
		param[i++] = '\0';
	i = 3;
	j = 0;
		if (buf[i] == '~')
	{
		while (home[j] != '\0')
		{
			param[j] = home[j];
			j++;
		}
		i = 4;
	}
	while(buf[i] != '\0')
	{
		param [j] = buf[i];
		i++;
		j++;
	}
	if (chdir(param) == -1)
		ft_putendl_fd("no such file or directory", 2);
	free(param);
    return (0);
}
