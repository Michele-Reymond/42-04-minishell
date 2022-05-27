/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:07 by vroch             #+#    #+#             */
/*   Updated: 2022/05/27 13:26:58 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* **************************************************************************
 *  parameter : buf = full line from readline.
 *  only execute in case of child
 */

int ms_b_other(char *buf, char **envp)
{
    int         err;
    char *const parm_list[] = {"/bin/ls", "-la", NULL};
    char *const env_parms[] = {"/bin/", NULL};
    int         pid;
  
    
    if (access(parm_list[0], X_OK) == 1)
        printf("command ok %s\n", parm_list[0]);

    getenv("path");
    pid=fork();
    if (pid == 0)
    {
        err = execve("/bin/ls", parm_list, env_parms);
        if (err == -1)
            printf("Error: command not executable !\n");
        else
            printf("OK");
        exit(0);
    }
    else
    {
        waitpid(pid, &err, WUNTRACED);
        printf("Apres Fork\n");
    }
    return(0);
}
