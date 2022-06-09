/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:58:02 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/09 11:14:36 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    which_redir(t_redir *r, char *cmd)
{
    int		*nbr1;
	int		*nbr2;

    nbr1 = check_redir(cmd, '>');
	nbr2 = check_redir(cmd, '<');
    if (nbr2[0] > 0)
        r->redir = ft_strdup("<");
    else if (nbr2[1] > 0)
        r->redir = ft_strdup("<<");
    else if (nbr1[0] > 0 )
        r->redir = ft_strdup(">");
    else if (nbr1[1] > 0)
        r->redir = ft_strdup(">>");
    else
        r->redir = ft_strdup("");
}

// remove redirection part of the cmd
char    *stock_cmd_part(char **token, int pos)
{
    int i;
    char *tmp;
    char *dst;

    i = 0;
    dst = ft_strdup("");
    while (token[i] != NULL)
    {
        if (!(i == pos || i == pos + 1))
        {
            tmp = ft_strjoin(dst, token[i]);
            free(dst);
            dst = tmp;
            tmp = ft_strjoin(dst, " ");
            free(dst);
            dst = tmp;
        }
        i++;
    }
    return (dst);
}

char **rebuilt_cmds(t_redir *r, int len)
{
    char **cmds;
    int i;

    i = 0;
    cmds = malloc(sizeof(char *) * len + 1);
    while (i < len)
    {
        cmds[i] = ft_strdup(r[i].cmd);
        i++;
    }
    return (cmds);
}

// create a truct with redirections infos
t_redir *stock_redir_infos(char **cmds)
{
    t_redir *r;
    int i;
    char **token;
    int pos;

    i = 0;
    r = malloc(sizeof(t_redir) * (tab_len(cmds) + 1));
    while (cmds[i] != NULL)
    {
        which_redir(&r[i], cmds[i]);
        r[i].index = i;
        token = tokenize(cmds[i]);
        pos = var_exist(token, r[i].redir);
        r[i].dest = ft_strtrim(ft_strdup(token[pos + 1]), " "); 
        r[i].cmd = stock_cmd_part(token, pos);
        tabfree(token);
        i++;
    }
    return (r);
}

int launch_out(t_redir r, t_tab *t, char *cmd)
{
    (void) r;
    (void) t;
    printf("Launch out:\n");
    printf("%s\n", cmd);
    printf("____________\n");
    return (0);
}

int launch_out_d(t_redir r, t_tab *t, char *cmd)
{
    (void) r;
    (void) t;
    printf("Launch out double:\n");
    printf("%s\n", cmd);
    printf("____________\n");
    return (0);
}

int launch_in(t_redir r, t_tab *t, char *cmd)
{
    (void) r;
    (void) t;
    printf("Launch in:\n");
    printf("%s\n", cmd);
    printf("____________\n");
    return (0);
}

int launch_in_d(t_redir r, t_tab *t, char *cmd)
{
    (void) r;
    (void) t;
    printf("Launch in double:\n");
    printf("%s\n", cmd);
    printf("____________\n");
    return (0);
}

int launch_redir(t_redir r, t_tab *t, char *cmd)
{
    int ret;

    if (!ft_strncmp(r.redir, ">", 1) && cmd[1] == '\0')
		ret = launch_out(r, t, cmd);
    if (!ft_strncmp(r.redir, "<", 1) && cmd[1] == '\0')
		ret = launch_in(r, t, cmd);
    if (!ft_strncmp(r.redir, ">>", 2) && cmd[2] == '\0')
		ret = launch_out_d(r, t, cmd);
    if (!ft_strncmp(r.redir, "<<", 2) && cmd[2] == '\0')
		ret = launch_in_d(r, t, cmd);
    else
        ret = 0;
    return (ret);
}

// launch cmds with redirections symbol
void    launch_with_redir(t_parse p, t_tab *t)
{
    t_redir *r;
    int     i;
    int     len;
    
    i = 0;
    r = stock_redir_infos(p.cmds);
    len = tab_len(p.cmds);
    tabfree(p.cmds);
    p.cmds = rebuilt_cmds(r, len);
    while (p.cmds[i] != NULL)
    {
        if(launch_redir(r[i], t, p.cmds[i]))
            return ;
        i++;
    }
}

// checker ce qu'il se passe quand il n'y a pas de redir dans une des commandes
// par exemple : cat test > outfile | echo coucou

// 1. faire la redirections des chevrons
// 2. action sur le fichier de sortie/entrée
// 3. si il y a un pipe la redirection du pipe écrase la redirection précédente
