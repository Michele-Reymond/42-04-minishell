/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:15:36 by mreymond          #+#    #+#             */
/*   Updated: 2022/07/28 16:45:45 by mreymond         ###   ########.fr       */
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
            else if (pos != 0 && pos != nbr && 
                    !(i == pos - 1 && j == 0) && !(i == pos && j == 1))
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
            else if (pos != 0 && pos != nbr && 
                    (i == pos - 1 && j == 0) && (i == pos && j == 1))
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
