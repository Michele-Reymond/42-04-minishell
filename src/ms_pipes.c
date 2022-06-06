/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:15:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/06 12:40:42 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void closing_loop(int **fd, int pos, int nbr)
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
            if (!(i == pos && j == 0))
                if (!(i == pos + 1 && j == 1))
                    close(fd[i][j]);
            j++;
        }
        i++;
    }
}

void child_process(pid_t pid, int **fd, int pos, int nbr)
{
    int i;

    i = 0;
    pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
	{
		closing_loop(fd, pos, nbr);
        while (i <= pos)
        {
            printf("    ");
            i++;
        }
        printf("Hello!\n");
	}
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
    fd = malloc(sizeof(int *) * p.pipes);
    while (i < p.nbr_cmd)
    {
        fd[i] = malloc(sizeof(int) * 2);
        i++;
    }
    create_pipes(fd, p.pipes);
    i = 0;
    while (i < p.nbr_cmd)
    {
        child_process(pid[i], fd, i, p.nbr_cmd);
        i++;
    }
    close(fd[p.pipes][0]);
	close(fd[0][1]);
    i = 0;
    while (i < p.nbr_cmd)
    {
        waitpid(pid[0], &status, 0);
        i++;
    }
}