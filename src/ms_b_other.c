/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/06/01 13:30:22 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* **************************************************************************
 *  parameter : len of each element of PATH
 *   initialize the len array
 *   determine de size of each element and add it to the table
 *   and put in elem 99 the number of element discovered.
 */

static int	*path_len(int *len)
{
	char	*path;
	int		i;
	int		j;
	int		k;

	path = getenv ("PATH");
	i = 0;
	while (i < 100)
		len[i++] = 0;
	i = 0;
	j = 0;
	k = 0;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
		{
			len[j++] = k;
			k = 0;
		}
		i++;
		k++;
	}
	len[j++] = k;
	len[j++] = 1;
	len[99] = j;
	return (len);
}
/* **************************************************************************
 *  parameter : env_parms
 *   create the len array and execute path_len
 */

static char	**path_load(int *len, char **env_parms)
{
	char	*path;
	int		i;
	int		j;
	int		k;

	path = getenv ("PATH");
	printf("Path : %s\n", path);
	i = 0;
	j = 0;
	k = 0;
	while (path[i] != '\0' && j <= len[99])
	{
		if (path[i] == ':')
		{
			env_parms[j][k] = '/';
			k++;
			env_parms[j][k] = '\0';
			i++;
			j++;
			k = 0;
		} 
		else
		{
			env_parms[j][k] = path[i];
			// printf ("env_parms : %s", env_parms[j]);
			// fflush(stdout);
			i++;
			k++;
		}
	}
	env_parms[j][k] = path[i];
	j++;
	env_parms[j][0] = '\0';
	// null a inserer
	i = 0;
	while (i < len[99])
	{
		printf("env_parms[%d] = %s\n", i, env_parms[i]);
		i++;
	}
	return(env_parms);
}

/* **************************************************************************
 *  parameter : env_parms
 *   create the len array and execute path_len
 */
static char **path_parsing()
{
	int		i;
	int		*len;
	char	**env_parms;

	len = malloc (100 * sizeof(int));
	if (len == NULL)
		return(NULL);
	len = path_len(len);
	env_parms = malloc(len[99] * sizeof(char*));
	// printf("len[99] = %d\n", len[99]);
	i = 0;
	while(i < len[99])
	{
		if (len[i] > 0 && i != 99)
		{
		printf("len[%d] = %d\n", i, len[i]);
		env_parms[i] = malloc(len[i] + 2 * sizeof(char));
		if (env_parms[i] == NULL)
				return(env_parms);
		ft_memset(env_parms[i], len[i] + 1, '\0');
		}
		i++;
	}
	env_parms = path_load(len, env_parms);
	free(len);
	
	// i = 0;
	// printf ("Constr env_parms\n");
	// while (env_parms[i] != NULL)
	// {
	// 	printf ("%s\n",env_parms[i]);
	// 	i++;
	// }

	return(env_parms);

}
/* **************************************************************************
 *  parameter : buf
 *   
 */

static char **cmd_checking(char **parm_list, char **env_parms, char *buf)
{
	int i;
	int	j;
	char	*str;
	char	*cmd;
	int		err;

	
	cmd = malloc(ft_strlen(buf) + 1024 * sizeof(char));
	j = 0;
	while (buf[j] != ' ')
	{
		cmd[j] = buf[j];
		j++;
	}
	printf("cmd : %s\n",cmd);
	i = 0;
	while (env_parms != NULL)
	{
		str = ft_strjoin(env_parms[i], cmd);
		err = access(str, X_OK);	
		printf("err: %d %s\n",err,str);
		if (err == 0)
			break;
		i++;
	}
	parm_list[0] = str;

	return(parm_list);
}
/* **************************************************************************
 *  parameter : buf
 *   
 */

int ms_b_other(char *buf)
{
	char	**env_parms;
	char	**parm_list_t;
	int		i;
	int		j;
	int		k;
	int		err;
	// char	*cmd;
	//  char	*xparm_list[] = {"/bin/ls", "-la", NULL};
	//  char   *xenv_parms[] = {"/bin/", NULL};
	char	**parm_list;
	int		pid;
	env_parms = path_parsing();
	i = 0;
	// printf ("Ret env_parms\n");
	// while (env_parms[i] != NULL)
	// {
	// 	printf ("%s\n",env_parms[i]);
	// 	i++;
	// }


	// --------------------------------------------
	parm_list_t = ft_split(buf, ' ');
	i = 0;
	// j = 0;
	// k = 0;
	
	while (parm_list_t[i] != NULL)
			i++;
	i = i + 1;
	parm_list = malloc(i  * sizeof(char));
	j = 0;
	while (j < i)
	{
		parm_list[j] = malloc(1024 * sizeof (char));
		ft_memset (parm_list[j], '\0', ft_strlen(buf));
		printf ("j : %d >%s<\n", j, parm_list[j]);
		j++;
	}
	i = 0;
	j = 0;
	k = 0;
	//  construction de param_list
	parm_list = cmd_checking(parm_list, env_parms, buf);
	
	// test de param list avec access
	err = 0;
	err = access(parm_list[0], X_OK);
	if (err == 0)
		printf("command OK %s\n", parm_list[0]);
	else
		printf("command KO %s\n", parm_list[0]);

// ----------------------
	pid=fork();
	if (pid == 0)
	{
		err = 0;
		err = execve(parm_list[0], parm_list, env_parms);
		printf("err = %d\n", err);
		if (err == -1)
			printf("Error: command not executable !\n");;
		exit(0);
	}
	else
	{
		waitpid(pid, &err, WUNTRACED);
		printf("Apres Fork\n");
	}
	return(0);
}
