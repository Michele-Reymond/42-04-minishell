/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:15:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/16 14:31:48 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// nbr : nombres de pipes()
// pos : dans quel process on est
void closing_loop_in(int **fd, int pos, int nbr)
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
            if (pos == 0 && !(i == 0 && j == 1))
                close(fd[i][j]);
            else if (pos != 0 && pos != nbr && !(i == pos - 1 && j == 0) && !(i == pos && j == 1))
                close(fd[i][j]);
            else if (pos == nbr && !(i == pos - 1 && j == 0))
                close(fd[i][j]);
            j++;
        }
        i++;
    }
}

void closing_loop_out(int **fd, int pos, int nbr)
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
            if (pos == 0 && (i == 0 && j == 1))
                close(fd[i][j]);
            else if (pos != 0 && pos != nbr && (i == pos - 1 && j == 0) && (i == pos && j == 1))
                close(fd[i][j]);
            else if (pos == nbr && (i == pos - 1 && j == 0))
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
void child_process(int **fd, int pos, int nbr)
{
    closing_loop_in(fd, pos, nbr);
    if (pos == 0)
        dup2(fd[pos][1], STDOUT_FILENO);
    else if (pos != 0 && !(pos == nbr))
    {
        dup2(fd[pos - 1][0], STDIN_FILENO);
        dup2(fd[pos][1], STDOUT_FILENO);
    }
    else
        dup2(fd[pos - 1][0], STDIN_FILENO);
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
    int k;

    i = 0;
    k = 0;
    pid = malloc(sizeof(pid_t) * p.nbr_cmd);
    fd = malloc(sizeof(int *) * p.pipes);
    while (i < p.pipes)
    {
        fd[i] = malloc(sizeof(int) * 2);
        i++;
    }
    create_pipes(fd, p.pipes);
    i = 0;
    while (i < p.nbr_cmd)
    {
        pid[i] = fork();
        if (pid[i] < 0)
            return ;
        if (pid[i] == 0)
        {
            child_process(fd, i, p.pipes);
            if (launch_cmds(p.cmds[i], t))
                other_basic(p.cmds[i], t);
            closing_loop_out(fd, i, p.pipes);
            while (k < p.pipes)
            {
                free(fd[k]);
                k++;
            }
            free(fd);
            free(pid);
            exit (0);
        }
        i++;
    }
    if (pid != 0)
    {
        parent_closing_loop(fd, p.pipes);
        i = 0;
        while (i < p.nbr_cmd)
        {
            waitpid(pid[i], &status, 0);
            i++;
        }
        i = 0;
        while (i < p.pipes)
        {
            free(fd[i]);
            i++;
        }
        free(fd);
        free(pid);
    }
}

///pipes & redirections

void launch_pipes_with_redir(t_parse p, t_tab *t)
{
    pid_t	*pid;
    int		**fd;
    int		status;
    int     i;
    int k;

    i = 0;
    k = 0;
    pid = malloc(sizeof(pid_t) * p.nbr_cmd);
    fd = malloc(sizeof(int *) * p.pipes);
    while (i < p.pipes)
    {
        fd[i] = malloc(sizeof(int) * 2);
        i++;
    }
    create_pipes(fd, p.pipes);
    i = 0;
    while (i < p.nbr_cmd)
    {
        pid[i] = fork();
        if (pid[i] < 0)
            return ;
        if (pid[i] == 0)
        {
            child_process(fd, i, p.pipes);
            launching_redirs(p.cmds[i], t);
            closing_loop_out(fd, i, p.pipes);
            while (k < p.pipes)
            {
                free(fd[k]);
                k++;
            }
            free(fd);
            free(pid);
            exit (0);
        }
        i++;
    }
    if (pid != 0)
    {
        parent_closing_loop(fd, p.pipes);
        i = 0;
        while (i < p.nbr_cmd)
        {
            waitpid(pid[i], &status, 0);
            i++;
        }
        i = 0;
        while (i < p.pipes)
        {
            free(fd[i]);
            i++;
        }
        free(fd);
        free(pid);
    }
}