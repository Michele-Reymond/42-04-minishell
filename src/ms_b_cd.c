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
 *   / --> missing in last char of param && char = ' '
 *   
 *   
 */
int ms_b_cd(char *buf)
{
	char	*param;
	int		i;
	char	cwd[1024];
	int		err_code;

	param = malloc((strlen(buf) -3) * sizeof(char));
	i = 3;
	while(i < strlen(buf))
	{
		param [i-3] = buf[i];
		i++;
	}
	//printf("getcwd: %s\n",getcwd(cwd, 1024));
	printf ("param: >%s<\n",param);
	
 
    err_code = chdir(param);
	//printf("err_code: %d\n", err_code);
	//printf("getcwd: %s\n",getcwd(cwd, 1024));
	if (err_code == -1)
	{
		printf("no such file or directory %s\n", param);
	}

	free(param);

    return (0);
}
