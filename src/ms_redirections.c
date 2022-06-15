/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:58:02 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/15 10:49:48 by mreymond         ###   ########.fr       */
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
    char *trimmed;

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
    trimmed = ft_strtrim(dst, " ");
    free(dst);
    return (trimmed);
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
    cmds[i] = NULL;
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
        if (*r[i].redir == '\0')
        {
            r[i].dest = ft_strdup("");
            r[i].cmd = ft_strdup(cmds[i]);
        }
        else 
        {
            token = tokenize(cmds[i]);
            pos = var_exist(token, r[i].redir);
            r[i].dest = ft_strtrim(ft_strdup(token[pos + 1]), " "); 
            r[i].cmd = stock_cmd_part(token, pos);
            tabfree(token);
        }
        i++;
    }
    return (r);
}

void	check_files_in(char *file)
{
	if (access(file, F_OK) != 0)
	{
		printf("minishell: %s : %s \n", file,  strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (access(file, R_OK) != 0)
	{
		printf("minishell: %s : %s \n", file,  strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	check_files_out(char *file)
{
	if (access(file, F_OK) != 0)
		open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(file, W_OK) != 0)
	{
		printf("minishell: %s : %s \n", file,  strerror(errno));
		exit(EXIT_FAILURE);
	}
}

// >
void launch_out(t_redir r, t_tab *t, char *cmd)
{
    int		outfile;

    check_files_out(r.dest);
	outfile = open(r.dest, O_WRONLY);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// >>
void launch_out_d(t_redir r, t_tab *t, char *cmd)
{
    int		outfile;

    check_files_out(r.dest);
	outfile = open(r.dest, O_WRONLY | O_APPEND);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// <
void launch_in(t_redir r, t_tab *t, char *cmd)
{
    int		infile;

    check_files_in(r.dest);
	infile = open(r.dest, O_RDONLY);
	if (infile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    other_redir_and_fork(cmd, t, infile, STDIN_FILENO);
}

// <<
void launch_in_d(t_redir r, t_tab *t, char *cmd)
{
    int     tmpfile;
    char    *input;
    char    *newcmd;
    pid_t	pid;
    int		status;

	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
	{
        while ((input = readline("> ")) != NULL) 
        {
            if (strlen(input) > 0)
            {
                if (!ft_strncmp(input, r.dest, ft_strlen(r.dest)))
                    break;
                write(tmpfile, input, ft_strlen(input));
                write(tmpfile, "\n", 1);
            }
            free(input);
        }
        newcmd = ft_strjoin(cmd, " .heredoc");
        other_basic(newcmd, t);
        close(tmpfile);
		exit (0);
	}
	else {
		waitpid(pid, &status, 0);
        close(tmpfile);
        unlink(".heredoc");
	}


    // dup2(tmpfile, STDOUT_FILENO);
    // while ((input = readline("> ")) != NULL) 
	// {
	// 	if (strlen(input) > 0)
	// 	{
	// 		if (!ft_strncmp(input, r.dest, ft_strlen(r.dest)))
	// 			break;
	// 		printf("%s\n", input);
	// 	}
  	//   	free(input);
	// }
    // newcmd = ft_strjoin(cmd, " ./tmp/.redir");
    // other_with_fork(newcmd, t);
}

void launch_redir(t_redir r, t_tab *t, char *cmd)
{
    if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		launch_out(r, t, cmd);
    else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		launch_in(r, t, cmd);
    else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		launch_out_d(r, t, cmd);
    else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		launch_in_d(r, t, cmd);
}

// launch cmds with redirections symbol
void    launch_with_redir(t_parse p, t_tab *t)
{
    t_redir *r;
    // int     i;
    int     len;
    
    // i = 0;
    r = stock_redir_infos(p.cmds);
    len = tab_len(p.cmds);
    tabfree(p.cmds);
    p.cmds = rebuilt_cmds(r, len);
    if (p.nbr_cmd == 1)
        launch_redir(r[0], t, p.cmds[0]);
    else
    {
        // while (p.cmds[i] != NULL)
        // {
        //     printf("%d: %s\n", i, p.cmds[i]);
        //     launch_redir(r[i], t, p.cmds[i]);
        //     i++;
        // }
    }
}

// i il y a un pipe la redirection du pipe écrase la redirection précédente?

// 0. terminer le heredoc
// 1. lancer les redir avec les builtins car la je lance que les other!!
// 2. lancer les redir et les pipes
// 3. signaux
// 4. .minishell
// 5. regler les bugs
// 6. checker les leaks et les closes de fichiers
