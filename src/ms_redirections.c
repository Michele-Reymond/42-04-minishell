/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:58:02 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/08 22:05:28 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//trouver un moyen pour savoir quel redir correspond à quel commande

void    which_redir(t_redir *r, t_parse p)
{
    if (p.redir_in > 0)
        r->redir = ft_strdup("<");
    else if(p.redir_in_d > 0)
        r->redir = ft_strdup("<<");
    else if (p.redir_out > 0 )
        r->redir = ft_strdup(">");
    else if (p.redir_out_d > 0)
        r->redir = ft_strdup(">>");
    else
        r->redir = NULL;
}

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

t_redir *stock_redir_infos(t_parse p, char **cmds)
{
    t_redir *r;
    int i;
    char **token;
    int pos;

    i = 0;
    r = malloc(sizeof(t_redir) * tab_len(cmds) + 1);
    while (cmds[i] != NULL)
    {
        which_redir(&r[i], p);
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

void    launch_with_redir(t_parse p, t_tab *t)
{
    t_redir *r;
    (void) t;
    (void) r;
    int i = 0;
    
    r = stock_redir_infos(p, p.cmds);
    while (p.cmds[i] != NULL)
    {
        printf("%d --------\n", i);
        printf("index : %d\n", r[i].index);
        printf("dest: %s\n", r[i].dest);
        printf("redir: %s\n", r[i].redir);
        printf("cmd: %s\n", r[i].cmd);
        i++;
    }
}
