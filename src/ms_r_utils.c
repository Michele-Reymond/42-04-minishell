/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_r_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:50:43 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/09 11:08:17 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check which redirection it is and stock in the redirection struct
// void    which_redir(t_redir *r, char *cmd)
// {
//     int		*nbr1;
// 	int		*nbr2;

//     nbr1 = check_redir(cmd, '>');
// 	nbr2 = check_redir(cmd, '<');
//     if (nbr2[0] > 0)
//         r->redir = ft_strdup("<");
//     else if (nbr2[1] > 0)
//         r->redir = ft_strdup("<<");
//     else if (nbr1[0] > 0 )
//         r->redir = ft_strdup(">");
//     else if (nbr1[1] > 0)
//         r->redir = ft_strdup(">>");
//     else
//         r->redir = NULL;
// }

// // remove redirection part of the cmd
// char    *stock_cmd_part(char **token, int pos)
// {
//     int i;
//     char *tmp;
//     char *dst;

//     i = 0;
//     dst = ft_strdup("");
//     while (token[i] != NULL)
//     {
//         if (!(i == pos || i == pos + 1))
//         {
//             tmp = ft_strjoin(dst, token[i]);
//             free(dst);
//             dst = tmp;
//             tmp = ft_strjoin(dst, " ");
//             free(dst);
//             dst = tmp;
//         }
//         i++;
//     }
//     return (dst);
// }

// char **rebuilt_cmds(t_redir *r, int len)
// {
//     char **cmds;
//     int i;

//     i = 0;
//     cmds = malloc(sizeof(char *) * len + 1);
//     while (i < len)
//     {
//         cmds[i] = ft_strdup(r[i].cmd);
//         i++;
//     }
//     return (cmds);
// }

// // create a truct with redirections infos
// t_redir *stock_redir_infos(char **cmds)
// {
//     t_redir *r;
//     int i;
//     char **token;
//     int pos;

//     i = 0;
//     r = malloc(sizeof(t_redir) * tab_len(cmds) + 2);
//     while (cmds[i] != NULL)
//     {
//         which_redir(&r[i], cmds[i]);
//         r[i].index = i;
//         token = tokenize(cmds[i]);
//         pos = var_exist(token, r[i].redir);
//         r[i].dest = ft_strtrim(ft_strdup(token[pos + 1]), " "); 
//         r[i].cmd = stock_cmd_part(token, pos);
//         tabfree(token);
//         i++;
//     }
//     return (r);
// }
