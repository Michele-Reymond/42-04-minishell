/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:15:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/06 19:55:26 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// nbr : nombres de pipes()
// pos : dans quel process on est
void closing_loop(int **fd, int pos, int nbr)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < nbr + 1)
    {
        j = 0;
        while (j < 2)
        {
            if (!(i == pos && j == 0) && !(i == pos + 1 && j == 1))
                close(fd[i][j]);
            j++;
        }
        i++;
    }
}

// nbr : nombres de pipes()
void parent_closing_loop(int **fd, int nbr)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < nbr)
    {
        j = 0;
        while (j < 2)
        {
            close(fd[i][j]);
            j++;
        }
        i++;
    }
}

// lancer les processus enfants
int child_process(pid_t pid, int **fd, int pos, int nbr)
{
    pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		closing_loop(fd, pos, nbr);
        if (!(pos == nbr - 1))
        {
            dup2(fd[pos][0], STDIN_FILENO);
	        dup2(fd[pos + 1][1], STDOUT_FILENO);
        }
        else
            dup2(fd[pos][0], STDIN_FILENO);
        return (1);
	}
    return (0);
}

void create_pipes(int **fd, int nbr)
{
    int i;

    i = 0;
    while (i < nbr)
    {
        if (pipe(fd[i]) == -1)
            return ;
        i++;
    }
}

void launch_with_pipes(t_parse p, t_tab *t)
{
    pid_t	*pid;
    int		**fd;
    int		status;
    int     i;

    (void) t;
    i = 0;
    pid = malloc(sizeof(pid_t) * p.nbr_cmd);
    fd = malloc(sizeof(int *) * p.nbr_cmd + 1);
    while (i <= p.nbr_cmd)
    {
        fd[i] = malloc(sizeof(int) * 2);
        i++;
    }
    create_pipes(fd, p.nbr_cmd + 1);
    i = 0;
    while (i < p.nbr_cmd)
    {
        if (child_process(pid[i], fd, i, p.nbr_cmd))
        {
            launch_cmds(p.cmds[i], t);
            exit(0) ;
        }
        i++;
    }
    parent_closing_loop(fd, p.nbr_cmd + 1);
    i = 0;
    while (i < p.nbr_cmd)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
}