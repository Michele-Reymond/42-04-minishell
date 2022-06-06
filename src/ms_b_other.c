/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/06/03 14:48:24 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* **************************************************************************
 *  parameter : len (empty and not yet allocated)
 *  retour : len
 * 	  malloc of len --> 100 occurences maxi
 *    determine size of the PATH, warning last segment not ended by : 
 *	  determine size of the CURRENT WORKING DIRECTORY
 *	  len[99] is the number of rows required + 1 for '\0'
 *   
 * */

static int	*ot_path_size(int *len)
{
	char	*path;
	char	current_wd[1024];
	int		i;
	int		j;
	int		k;

	len = malloc(100 * sizeof(int));
	if (len == NULL)
		return (NULL);
	i = 0;
	while (i != 100)
		len[i++] = 0;
	path = getenv("PATH");
	i = 0;
	j = 0;
	k = 1;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
		{
			len[j++] = k + 1;
			k = 0;
		}
		i++;
		k++;
	}
	len[j++] = k + 1;
	getcwd(current_wd, 1024);
	len[j++] = ft_strlen(current_wd) + 1;
	len[j++] = 1;
	len[99] = j;
	return (len);
}
/* **************************************************************************
 *  parameter : env_parm (empty but allocated)
 *  retour : env_parm
 * 	 complete the ligne of path with a / and finish with '\0'
 *   warning last segment not ended by :
 */

static char	**ot_path_fulfill(char **env_parms)
{
	char	*path;
	char	current_wd[1024];
	int		i;
	int		j;
	int		k;

	path = getenv ("PATH");
	i = 0;
	j = 0;
	k = 0;
	while (path[i] != '\0')
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
			i++;
			k++;
		}
	}
	env_parms[j][k] = '/';
	k++;
	env_parms[j][k] = '\0';
	j++;
	getcwd(current_wd, 1024);
	k = 0;
	i = 0;
	while (current_wd[i] != '\0')
		env_parms[j][k++] = current_wd[i++];
	env_parms[j][k++] = '/';
	env_parms[j][k++] = '\0';
	j++;
	env_parms[j][0] = '\0';
	return (env_parms);
}

/* **************************************************************************
 *  parameter : env_parm (empty and not yet allocated)
 *  retour : env_parm
 * 	 detertmine len for mallocs
 * 	 perform mallocs (+1 for '\0')
 *   fullfil env_parm
 */

static char	**ot_path_parsing(char **env_parms)
{
	int	*len;
	int	i;

	len = NULL;
	len = ot_path_size(len);
	env_parms = malloc(len[99] * sizeof(char *));
	if (env_parms == NULL)
		return (NULL);
	i = 0;
	while (i < len[99])
	{
		env_parms[i] = malloc(len[i] * sizeof (char));
		if (env_parms[i] == NULL)
		{	
			return (NULL);
		}
		i++;
	}
	env_parms = ot_path_fulfill(env_parms);
	free(len);
	return (env_parms);
}
/* **************************************************************************
 *  parameter : cmd
 *  retour : cmd
 * 	 determin if pattern ./ present
 * 	 remove all . and /
 *   remove extra spaces remainings
 *   return the new cmd
 * exit
 */
static char	*ot_cmd_path(char *cmd)
{
	int i;

	i = 0;
	if (ft_strncmp(cmd, "./",2))
	{
		while (cmd[i] != '\0')
		{
			if (cmd[i] == '.')
				cmd[i] = ' ';
			if (cmd[i] == '/')
				cmd[i] = ' ';
			
			i++;
		}
	}	
	cmd = ft_strtrim(cmd, " ");
	printf("cmd : >%s<\n",cmd);

	return(cmd);

}

/* **************************************************************************
 *  parameter : parm_list & env_parms & buf
 *  retour : parm_list
 * 	  creation of the element[0] with the accurate path and the command
 */

static char	*ot_cmd_checking(char **env_parms, char *buf)
{
	int		i;
	int		j;
	char	*str;
	char	*cmd;
	int		err;

	cmd = ft_calloc(ft_strlen(buf) + 1024, 4);
	j = 0;
	while (buf[j] != ' ' && buf[j] != '\0')
	{
		cmd[j] = buf[j];
		j++;
	}
	if (cmd[0] == '.' || cmd[0] == '/')
		cmd = ot_cmd_path(cmd);
	

	i = 0;
	while (env_parms[i][0] != '\0')
	{
		str = ft_strjoin(env_parms[i], cmd);
		err = access(str, X_OK);
		if (err == 0)
			break ;
		i++;
	}
	free (cmd);
	return (str);
}

/* **************************************************************************
 *  parameter : env_parms & parm_list & buf & cmd
 *  retour : parm_list
 *   construct the parm_list 
 *   set one extra row for the '\0'
 * 
 */

char	**ot_parm_parsing(char **parm_list, char *buf, char *cmd)
{
	char	**parm_list_t;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	parm_list_t = ft_split(buf, ' ');
	while (parm_list_t[i] != NULL)
		i++;
	parm_list = malloc (i + 1 * sizeof(char *));
	i = 0;
	while (parm_list_t[i] != NULL)
	{
		if (i == 0)
			len = ft_strlen(cmd);
		else
			len = ft_strlen(parm_list_t[i]);
		parm_list[i] = malloc(len + 1 * sizeof(char));
		i++;
	}
		parm_list[i] = malloc(1 * sizeof(char));
	i = 0;
	while (parm_list_t[i] != NULL)
	{
		if ( i == 0)
		{
			j = 0;
			while(cmd[j] != '\0')
			{
				parm_list[i][j] = cmd[j];
				j++;
			}
			parm_list[i][j] = '\0';
		}
		else
		{
			j = 0;
			while(parm_list_t[i][j] != '\0')
			{
				parm_list[i][j] = parm_list_t[i][j];
				j++;
			}
			parm_list[i][j] = '\0';
		}
		i++;
	}
	parm_list[i][0] = '\0';
	return(parm_list);
	
}

/* **************************************************************************
 *  parameter : buf --> full command issued from readline
 *  retour : 0
 *   construct the env_param with PATH & current PW
 *   check the path required by the cmd
 *   construct the parm_list with env_parm & buf
 *   fork to execute execve
 * 
 */

int ms_b_other(char *buf)
{
	char	**env_parms;
	char	**parm_list;
	char	*xparm_list[20] = {NULL};	
	char	*xenv_parms[20] = {NULL};
	char	*cmd;
	int		i;
	int		err;
	int		pid;

	env_parms = NULL;
	env_parms = ot_path_parsing(env_parms);
	cmd = ot_cmd_checking(env_parms, buf);
	parm_list = NULL;
	parm_list = ot_parm_parsing(parm_list, buf, cmd);
	err = 0;
	err = access(parm_list[0], X_OK);
	if (err != 0)
		printf("Error: command not found %s\n", parm_list[0]);
	i = 0;
	while (i < 20 && parm_list[i][0] != '\0')
	{
		xparm_list[i] = parm_list[i];
		i++;
	}
	i = 0;
	while (i < 20 && env_parms[i][0] != '\0')
	{
		xenv_parms[i] = env_parms[i];
		i++;
	}
	free (parm_list);
	free (env_parms);
	pid = fork();
	if (pid == 0)
	{
		err = 0;
		err = execve(xparm_list[0], xparm_list, xenv_parms);
		printf("err = %d\n", err);
		if (err == -1)
			printf("Error: command not executable !\n");
		exit (0);
	}
	else
	{
		waitpid(pid, &err, WUNTRACED);
	}
	return (0);
}