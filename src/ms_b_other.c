/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/06/01 15:47:38 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "minishell.h"
#include "libft/libft.h"
#include "libft/ft_memset.c"
#include "libft/ft_strjoin.c"
#include "libft/ft_strlen.c"
#include "libft/ft_split.c"
#include "libft/ft_bzero.c"
/* **************************************************************************
 *  parameter : len (empty and not yet allocated)
 *  retour : len
 * 	  malloc of len --> 100 occurences maxi
 *    determine size of the PATH, warning last segment not ended by : 
 *	  determine size of the CURRENT WORKING DIRECTORY
 *	  len[99] is the number of rows required + 1 for '\0'
 *   
 * */

static int *path_size (int *len)
{
	char	*path;
	char	current_wd[1024];
	int		i;
	int		j;
	int		k;

	len = malloc(100 * sizeof(int));
	i = 0;
	while (i != 100)
		len[i++] = 0;
	if (len == NULL)
		return(NULL);
	path = getenv ("PATH");
	printf("path : %s\n",path);

	i = 0;
	j = 0;
	k = 1;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
		{
			len[j++] = k + 1;
			//len[j++] = 1024;
			k = 0;
		}
		i++;
		k++;
	}
	len[j++] = k + 1;
	//len[j++] = 1024;
	
	getcwd(current_wd, 1024);
	len[j++] = ft_strlen(current_wd) + 1;
	//len[j++] = 1024;
	len[j++] = 1;
	len[99] = j;
	for(i=0 ; i < len[99] ; i++)
	{
		printf("len %d: %d\n", i, len[i]);
	}
	i = 99;
	printf("len %d: %d\n", i, len[i]);

	return(len);
}
/* **************************************************************************
 *  parameter : env_parm (empty but allocated)
 *  retour : env_parm
 * 	 complete the ligne of path with a / and finish with '\0'
 *   warning last segment not ended by :
 */

static char **path_fulfill(char **env_parms, int *len)
{
	
	char	*path;
	char	current_wd[1024];
	int		i;
	int		j;
	int		k;
	char	*tmp;

	path = getenv ("PATH");
	printf("Path : %s\n", path);
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
			printf("env_parms %d = %d(%d): %s\n",j, strlen(env_parms[j]),len[j], env_parms[j]);
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
	//env_parms[j][k] = path[i];
	//k++;
	env_parms[j][k] = '/';
	k++;
	env_parms[j][k] = '\0';
	printf("env_parms %d = %d(%d): %s\n",j, strlen(env_parms[j]),len[j], env_parms[j]);
	
	j++;
	getcwd(current_wd, 1024);
	//printf("%s\n",current_wd);
	k = 0;
	i = 0;
	while(current_wd[i] != '\0')
		env_parms[j][k++] = current_wd[i++];
	env_parms[j][k++] = '/';
	env_parms[j][k++] = '\0';
	printf("env_parms %d = %d(%d): %s\n",j, strlen(env_parms[j]),len[j], env_parms[j]);
	j++;
	env_parms[j][0] = '\0';
	printf("env_parms %d = %d(%d): %s\n",j, strlen(env_parms[j]),len[j], env_parms[j]);

	return(env_parms);
}


/* **************************************************************************
 *  parameter : env_parm (empty and not yet allocated)
 *  retour : env_parm
 * 	 detertmine len for mallocs
 * 	 perform mallocs (+1 for '\0')
 *   fullfil env_parm
 */

static char **path_parsing(char **env_parms)
{
	int	*len;
	int	i;
	int	j;
	len = path_size(len);

	env_parms = malloc(len[99] * sizeof(char*));
	//ft_memset (env_parms, '\0', len[99]);
	printf("%p \n", env_parms);
	if (env_parms == NULL)
		return(NULL);	
	i = 0;
	while(i < len[99])
	{
		printf("malloc len %d : %d\n",i, len[i]);
		env_parms[i] = malloc(len[i] * sizeof(char));
		if (env_parms[i] == NULL)
		{	
			printf("problem malloc\n");
			return(NULL);
		}
		//ft_memset (env_parms, '\0', len[i]);
		printf("%p %d\n", env_parms[i], i);
		i++;
	}
	env_parms = path_fulfill(env_parms, len);
	free(len);
	return(env_parms);
}

/* **************************************************************************
 *  parameter : parm_list & env_parms & buf
 *  retour : parm_list
 * 	  creation of the element[0] with the accurate path and the command
 */

static char *cmd_checking(char **env_parms, char *buf)
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
	free (cmd);

	return(str);
}


/* **************************************************************************
 *  parameter : env_parms & parm_list & buf & cmd
 *  retour : parm_list
 *   construct the parm_list 
 *   set one extra row for the '\0'
 * 
 */
char **parm_parsing(char **env_parms, char **parm_list, char *buf, char *cmd)
{
	char	**parm_list_t;
	int		i;
	int 	j;
	size_t	len;
	
	i = 0;
	parm_list_t = ft_split(buf, ' ');
	while (parm_list_t[i] != NULL)
		i++;
	parm_list = malloc(i + 1 * sizeof(char*));
	
	i = 0;
	while (parm_list_t[i] != NULL)
	{
		if (i == 0)
			len = ft_strlen(cmd);
		else
			len = ft_strlen(parm_list_t[i]);
		parm_list[i] = malloc(len + 1 * sizeof(char));
		printf ("parm_list[%d]: %d\n", i, len);
		i++;
	}
		parm_list[i] = malloc(1 * sizeof(char));
		printf ("parm_list[%d]: %d\n", i, 1);

	i = 0;
	while (parm_list_t[i] != NULL)
	{
		if ( i == 0)
		{
			j = 0;
			printf("cmd :%s\n",cmd);
			while(cmd[j] != '\0')
			{
				parm_list[i][j] = cmd[j];
				j++;
			}
			parm_list[i][j] = '\0';
			printf("parm_list[%d] %s\n",i,parm_list[i]);
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
			printf("parm_list[%d] %s\n",i,parm_list[i]);
		}
		i++;
	}
	parm_list[i][0] = '\0';
	printf("parm_list[%d] %s\n",i,parm_list[i]);
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
	//   char	*xparm_list[] = {"/usr/bin/ls", "-la", NULL};
	//   char  *xenv_parms[] = {"/bin/", "/usr/sbin/", NULL};	
	  char	*xparm_list[20] = {NULL};	
	  char  *xenv_parms[20] = {NULL};
	char	*cmd;
	int		i;
	int		err;
	int		pid;
	printf("buf: %s\n", buf);
	env_parms = path_parsing(env_parms);
	cmd = cmd_checking(env_parms, buf);
	parm_list = parm_parsing(env_parms,parm_list, buf, cmd);

	
	// test de param list avec access
	err = 0;
	err = access(parm_list[0], X_OK);
	if (err == 0)
		printf("command OK %s\n", parm_list[0]);
	else
		printf("command KO %s\n", parm_list[0]);

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
	
// ----------------------
	pid=fork();
	if (pid == 0)
	{
		err = 0;
		err = execve(parm_list[0], xparm_list, xenv_parms);
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

int main ()
{
    ms_b_other("ls -la");
}