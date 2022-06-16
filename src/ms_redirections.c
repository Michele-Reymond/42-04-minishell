/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:58:02 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/16 15:48:32 by mreymond         ###   ########.fr       */
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

void fork_and_launch_builtin(char *cmd, t_tab *t, int fd, int std)
{
    pid_t	pid;
	int		status;

    pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
	{
		dup2(fd, std);
		launch_cmds(cmd, t);
		exit (0);
	}
	else
		waitpid(pid, &status, 0);
}

// >
t_doors set_out(t_redir r, t_doors doors)
{
    int		outfile;
    t_doors new;

    check_files_out(r.dest);
	outfile = open(r.dest, O_TRUNC | O_WRONLY);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    new.in = doors.in;
    new.out = outfile;
    return (new);
}

// >
void launch_out(t_redir r, t_tab *t, char *cmd)
{
    int		outfile;

    check_files_out(r.dest);
	outfile = open(r.dest, O_TRUNC | O_WRONLY);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    if (is_a_builtin(cmd))
        fork_and_launch_builtin(cmd, t, outfile, STDOUT_FILENO);
    else
        other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// >>
t_doors set_out_d(t_redir r, t_doors doors)
{
    int		outfile;
    t_doors new;

    check_files_out(r.dest);
	outfile = open(r.dest, O_WRONLY | O_APPEND);
	if (outfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    new.in = doors.in;
    new.out = outfile;
    return (new);
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
    if (is_a_builtin(cmd))
        fork_and_launch_builtin(cmd, t, outfile, STDOUT_FILENO);
    else
        other_redir_and_fork(cmd, t, outfile, STDOUT_FILENO);
}

// <
t_doors set_in(t_redir r, t_doors doors)
{
    int		infile;
    t_doors new;

    check_files_in(r.dest);
	infile = open(r.dest, O_RDONLY);
	if (infile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    new.in = infile;
    new.out = doors.out;
    return (new);
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
   if (is_a_builtin(cmd))
        fork_and_launch_builtin(cmd, t, infile, STDIN_FILENO);
    else
        other_redir_and_fork(cmd, t, infile, STDIN_FILENO);
}

// <<
t_doors set_in_d(t_redir r, t_doors doors)
{
    int     tmpfile;
    char    *input;
    pid_t	pid;
    int		status;
    t_doors new;

	tmpfile = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    pid = fork();
	if (pid < 0)
    {
        perror("minishell: Fork: ");
		exit(EXIT_FAILURE);
    }
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
		exit(0);
	}
	else {
		waitpid(pid, &status, 0);
        new.in = tmpfile;
        new.out = doors.out;
        return (new);
	}
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
        // if (launch_cmds(newcmd, t))
            other_basic(newcmd, t);
        close(tmpfile);
		exit(0);
	}
	else {
		waitpid(pid, &status, 0);
        close(tmpfile);
        unlink(".heredoc");
	}
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

t_doors set_redirection(t_redir r, t_doors doors)
{
    t_doors new;

    if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		new = set_out(r, doors);
    else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		new = set_in(r, doors);
    else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		new = set_out_d(r, doors);
    else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		new = set_in_d(r, doors);
    else 
        new = doors;
    return (new);
}

void launch_multiple_redir(t_redir *r, t_tab *t, char **cmds)
{
    t_doors doors;
    char *newcmd;
    int i;

    i = 0;
    doors.in = STDIN_FILENO;
    doors.out = STDOUT_FILENO;
    while (cmds[i] != NULL)
    {
        doors = set_redirection(r[i], doors);
        i++;
    }
    if (access(".heredoc", F_OK) == 0)
    {
        newcmd = ft_strjoin(r[0].cmd, " .heredoc");
        free(r[0].cmd);
        r[0].cmd = newcmd;
    }
    if (is_a_builtin(r[0].cmd))
        launch_builtins_with_doors(r[0].cmd, t, doors);
    else
        other_doors_and_fork(r[0].cmd, t, doors);
    close(doors.in);
    close(doors.out);
    if (access(".heredoc", F_OK) == 0)
        unlink(".heredoc");
}

char *find_cmd(char **token, int start)
{
    char *cmd;
    char *tmp;

    tmp = ft_strdup(token[start - 1]);
    cmd = ft_strjoin(tmp, " ");
    free(tmp);
    while (token[start] != NULL && ft_strncmp(token[start], ">", 1) && ft_strncmp(token[start], "<", 1))
    {
        tmp = ft_strjoin(cmd, token[start]);
        free(cmd);
        cmd = ft_strjoin(tmp, " ");
        free(tmp);
        start++;
    }
    return (cmd);
}

char **join_cmd_and_redir(char *cmd, char **redirs)
{
    char **new;
    char *tmp;
    int i;
    int j;

    i = 0;
    j = 0;
    tmp = ft_strjoin(cmd, " ");
    new = malloc(sizeof(char *) * tab_len(redirs) + 1);
    while (redirs[i] != NULL)
    {
        if (redirs[i][0] == '<')
        {
            new[j] = ft_strjoin(tmp, redirs[i]);
            j++;
        }
        i++;
    }
    i = 0;
    while (redirs[i] != NULL)
    {
        if (redirs[i][0] == '>')
        {
            new[j] = ft_strjoin(tmp, redirs[i]);
            j++;
        }
        i++;
    }
    new[j] = NULL;
    free(tmp);
    return (new);
}

char **split_with_starting_redir(char **token, char *oldcmd)
{
    char *cmd;
    char *pos;
    int i;
    int j;
    int k;
    int		*nbr1;
	int		*nbr2;
    int     nbr;
    char **redirs;
    char **new;

    i = 0;
    j = 0;
    k = 0;
    cmd = ft_strtrim(find_cmd(token, 3), " ");
    pos = ft_strnstr(oldcmd, cmd, ft_strlen(oldcmd));
    nbr1 = check_redir(oldcmd, '>');
	nbr2 = check_redir(oldcmd, '<');
    nbr = nbr1[0] + nbr1[1] + nbr2[0] + nbr2[1];
    redirs = malloc(sizeof(char *) * nbr + 1);
    while (oldcmd[i] && &oldcmd[i] != pos)
        i++;
    redirs[k] = malloc(sizeof(char) * i);
    i = 0;
    while (oldcmd[i] && &oldcmd[i] != pos)
    {
        redirs[k][i] = oldcmd[i];
        i++;
    }
    redirs[k][i] = '\0';
    i += ft_strlen(cmd);
    k++;
    while (oldcmd[i] != '\0' && nbr > 1)
    {
        j = i;
        while (oldcmd[j] && (oldcmd[j] == '>' || oldcmd[j] == '<'))
            j++;
        while (oldcmd[j] && (oldcmd[j] != '>' || oldcmd[j] != '<'))
            j++;
        redirs[k] = malloc(sizeof(char) * j - i);
        j = 0;
        while (oldcmd[i] && (oldcmd[i] == '>' || oldcmd[i] == '<'))
        {
            redirs[k][j] = oldcmd[i];
            j++;
            i++;
        }
        while (oldcmd[i] && oldcmd[i] != '>' && oldcmd[i] != '<')
        {
            redirs[k][j] = oldcmd[i];
            j++;
            i++;
        }
        redirs[k][j] = '\0';
        k++;
    }
    redirs[k] = NULL;
    new = join_cmd_and_redir(cmd, redirs);
    return (new);
}

char **split_with_starting_cmd(char **token, char *oldcmd)
{
    char *cmd;
    int i;
    int j;
    int k;
    int		*nbr1;
	int		*nbr2;
    int     nbr;
    char **redirs;
    char **new;

    j = 0;
    k = 0;
    cmd = ft_strtrim(find_cmd(token, 1), " ");
    nbr1 = check_redir(oldcmd, '>');
	nbr2 = check_redir(oldcmd, '<');
    nbr = nbr1[0] + nbr1[1] + nbr2[0] + nbr2[1];
    redirs = malloc(sizeof(char *) * nbr + 1);
    i = ft_strlen(cmd);
    while (oldcmd[i] != '\0')
    {
        j = i;
        while (oldcmd[j] && (oldcmd[j] == '>' || oldcmd[j] == '<'))
            j++;
        while (oldcmd[j] && (oldcmd[j] != '>' || oldcmd[j] != '<'))
            j++;
        redirs[k] = malloc(sizeof(char) * j - i);
        j = 0;
        while (oldcmd[i] && (oldcmd[i] == '>' || oldcmd[i] == '<'))
        {
            redirs[k][j] = oldcmd[i];
            j++;
            i++;
        }
        while (oldcmd[i] && oldcmd[i] != '>' && oldcmd[i] != '<')
        {
            redirs[k][j] = oldcmd[i];
            j++;
            i++;
        }
        redirs[k][j] = '\0';
        k++;
    }
    redirs[k] = NULL;
    new = join_cmd_and_redir(cmd, redirs);
    return (new);
}

char **split_redir(char *cmd)
{
    char **token;
    char **new;

    token = tokenize(cmd);
    if (!ft_strncmp(token[0], ">", 1) || !ft_strncmp(token[0], "<", 1))
        new = split_with_starting_redir(token, cmd);
    else
    {
        new = split_with_starting_cmd(token, cmd);
    }
    tabfree(token);
    return (new);
}

char **tabjoin(char **tab1, char **tab2)
{
    char **new;
    int len;
    int i;
    int j;

    i = 0;
    j = 0;
    len = tab_len(tab1) + tab_len(tab2);
    new = malloc(sizeof(char *) * len + 1);
    while (tab1[i] != NULL)
    {
        new[i] = ft_strdup(tab1[i]);
        i++;
    }
    while (tab2[j] != NULL)
    {
        new[i] = ft_strdup(tab2[j]);
        i++;
        j++;
    }
    new[i] = NULL;
    return (new);
}

int nbr_of_redir(char *cmd)
{
    int		*nbr1;
	int		*nbr2;

    nbr1 = check_redir(cmd, '>');
	nbr2 = check_redir(cmd, '<');
    return (nbr1[0] + nbr1[1] + nbr2[0] + nbr2[1]);
}

char **add_to_tab(char **oldtab, char *str_to_add)
{
    char **new;
    int i;

    i = 0;
    new = malloc(sizeof(char *) * tab_len(oldtab) + 2);
    while (oldtab[i] != NULL)
    {
        new[i] = ft_strdup(oldtab[i]);
        i++;
    }
    new[i] = ft_strdup(str_to_add);
    i++;
    new[i] = NULL;
    return (new);
}

char **one_redir_pro_cmd(char **oldcmds)
{
    char    **new;
    char    **tmp1;
    char    **tmp2;
    int     i;

    i = 0;
    new = new_tab();
    while (oldcmds[i] != NULL)
    {
        if (nbr_of_redir(oldcmds[i]) == 0)
        {
            tmp1 = add_to_tab(new, oldcmds[i]);
            tabfree(new);
            new = tmp1;
        }
        else
        {
            tmp1 = split_redir(oldcmds[i]);
            tmp2 = tabjoin(new, tmp1);
            tabfree(new);
            tabfree(tmp1);
            new = tmp2;
        }
        i++;
    }
    return (new);
}

// this function is used in pipes with redir function
void    launching_redirs(char *cmd, t_tab *t)
{
    t_redir *r;
    char    **newcmds;
    char    **tmp;
    int     len;

    if (nbr_of_redir(cmd) == 0)
    {
        if (launch_cmds(cmd, t))
                other_basic(cmd, t);
    }
    else if (nbr_of_redir(cmd) == 1)
    {
        newcmds = add_to_tab(new_tab(), cmd);
        r = stock_redir_infos(newcmds);
        len = tab_len(newcmds);
        tabfree(newcmds);
        newcmds = rebuilt_cmds(r, len);
        launch_redir(r[0], t, newcmds[0]);
    }
    else if (nbr_of_redir(cmd) > 1)
    {
        tmp = add_to_tab(new_tab(), cmd);
        newcmds = one_redir_pro_cmd(tmp);
        r = stock_redir_infos(newcmds);
        len = tab_len(newcmds);
        launch_multiple_redir(r, t, newcmds);
    }
}

// launch cmds with redirections symbol
// this function is used in monitor
void    launch_with_redir(t_parse p, t_tab *t)
{
    t_redir *r;
    char    **newcmds;
    int     len;
    
    if (tab_len(p.cmds) == 1 && p.redir <= 1)
    {
        r = stock_redir_infos(p.cmds);
        len = tab_len(p.cmds);
        tabfree(p.cmds);
        p.cmds = rebuilt_cmds(r, len);
        launch_redir(r[0], t, p.cmds[0]);
    }
    else if (p.pipes == 0 && p.redir > 1)
    {
        newcmds = one_redir_pro_cmd(p.cmds);
        r = stock_redir_infos(newcmds);
        len = tab_len(newcmds);
        launch_multiple_redir(r, t, newcmds);
    }
    else
        launch_pipes_with_redir(p, t);
}

// 3. signaux
// 4. .minishell
// 5. regler les bugs
// 6. checker les leaks et les closes de fichiers et les protections de malloc

// BUGS : 

// - cat << FIN > test