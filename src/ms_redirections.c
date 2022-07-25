/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:58:02 by mreymond          #+#    #+#             */
/*   Updated: 2022/07/25 12:23:59 by mreymond         ###   ########.fr       */
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

// for each cmd we parse the cmd with parsing master and stock infos
void parse_for_redir_infos(char *cmd, t_redir *r, int index)
{
    t_tprint tp;
    int pos;
    int i;
    
    i = 0;
    tp = parsing_master(cmd);
    r->redir = NULL;
    while (tp.tab[i] != NULL && r->redir == NULL)
    {
        if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) && tp.tab[i][0] == '>' && ft_strlen(tp.tab[i]) == 1)
            r->redir = ft_strdup(">");
        else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) && tp.tab[i][0] == '>' && ft_strlen(tp.tab[i]) == 2)
            r->redir = ft_strdup(">>");
        else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) && tp.tab[i][0] == '<' && ft_strlen(tp.tab[i]) == 1)
            r->redir = ft_strdup("<");
        else if ((tp.print[i + 1] == 2 || tp.print[i + 1] == 5 ) && tp.tab[i][0] == '<' && ft_strlen(tp.tab[i]) == 2)
            r->redir = ft_strdup("<<");
        else if (tp.tab[i + 1] == NULL)
            r->redir = ft_strdup("");
        i++;
    }
    r->index = index;
    if (*(r->redir) == '\0')
    {
        r->dest = ft_strdup("");
        r->cmd = ft_strdup(cmd);
    }
    else 
    {
        pos = var_exist(tp.tab, r->redir);
        r->dest = ft_strtrim(ft_strdup(tp.tab[pos + 1]), " "); 
        r->cmd = stock_cmd_part(tp.tab, pos);
        tabfree(tp.tab);
    }
}

// create a truct with redirections infos
t_redir *stock_redir_infos(char **cmds)
{
    t_redir *r;
    int i;
    // char **token;
    // int pos;

    i = 0;
    r = malloc(sizeof(t_redir) * (tab_len(cmds) + 1));
    while (cmds[i] != NULL)
    {
        parse_for_redir_infos(cmds[i], &r[i], i);

        // which_redir(&r[i], cmds[i]);
        // r[i].index = i;
        // if (*r[i].redir == '\0')
        // {
        //     r[i].dest = ft_strdup("");
        //     r[i].cmd = ft_strdup(cmds[i]);
        // }
        // else 
        // {
        //     token = tokenize(cmds[i]);
        //     pos = var_exist(token, r[i].redir);
        //     r[i].dest = ft_strtrim(ft_strdup(token[pos + 1]), " "); 
        //     r[i].cmd = stock_cmd_part(token, pos);
        //     tabfree(token);
        // }
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

int	check_files_in_basic(char *file)
{
	if (access(file, F_OK) != 0)
	{
		printf("minishell: %s : %s \n", file,  strerror(errno));
		return (1);
	}
	if (access(file, R_OK) != 0)
	{
		printf("minishell: %s : %s \n", file,  strerror(errno));
		return (1);
	}
    return (0);
}

int	check_files_out_basic(char *file)
{
	if (access(file, F_OK) != 0)
		open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(file, W_OK) != 0)
	{
		printf("minishell: %s : %s \n", file,  strerror(errno));
		return (1);
	}
    return (0);
}

void fork_and_launch_builtin(char *cmd, t_tab *t, int fd, int std)
{
    pid_t	pid;
	int		status;
    t_tprint tp;

	tp = parsing_master(cmd);
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
    {
		waitpid(pid, &status, 0);
        if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == ' ' || cmd[2] == '\0'))
		    t = ms_b_cd(cmd, t);
        else if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == ' ' || cmd[6] == '\0'))
            t = ft_export(t, tp);
        else if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == ' ' || cmd[5] == '\0'))
            t = unset_var(t, tp.tab);
    }
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

// <
void launch_in_basic(t_redir r, t_tab *t, char *cmd)
{
    int		infile;

    if (check_files_in_basic(r.dest))
        return;
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
void launch_heredoc(char *stop)
{
    int     tmpfile;
    char    *input;
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
                if (!ft_strncmp(input, stop, ft_strlen(stop)))
                    break;
                write(tmpfile, input, ft_strlen(input));
                write(tmpfile, "\n", 1);
            }
            free(input);
        }
        close(tmpfile);
		exit(0);
	}
	else
    {
		waitpid(pid, &status, 0);
        close(tmpfile);
    }
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

t_doors set_in_d_in_pipe(t_doors doors)
{
    int     tmpfile;
    t_doors new;

	tmpfile = open(".heredoc", O_RDONLY);
	if (tmpfile < 0)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
    new.in = tmpfile;
    new.out = doors.out;
    return (new);
}

// <<
void launch_in_d_in_pipe(t_tab *t, char *cmd)
{
    char    *newcmd;

    newcmd = ft_strjoin(cmd, " .heredoc");
    if (launch_cmds(newcmd, t))
        other_basic(newcmd, t);
}

// <<
void launch_in_d(t_redir r, t_tab *t, char *cmd)
{
    int     tmpfile;
    int     fd;
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
        newcmd = ft_strdup(cmd);
        fd = open(".heredoc", O_RDONLY);
        dup2(fd, STDIN_FILENO);
        if (launch_cmds(newcmd, t))
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

void launch_redir_in_pipe(t_redir r, t_tab *t, char *cmd)
{
    if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		launch_out(r, t, cmd);
    else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		launch_in(r, t, cmd);
    else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		launch_out_d(r, t, cmd);
    else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		launch_in_d_in_pipe(t, cmd);
}

void launch_redir(t_redir r, t_tab *t, char *cmd)
{
    if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		launch_out(r, t, cmd);
    else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		launch_in_basic(r, t, cmd);
    else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		launch_out_d(r, t, cmd);
    else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		launch_in_d(r, t, cmd);
}

t_doors set_redir_in_pipe(t_redir r, t_doors doors)
{
    t_doors new;

    if (!ft_strncmp(r.redir, ">", 1) && r.redir[1] == '\0')
		new = set_out(r, doors);
    else if (!ft_strncmp(r.redir, "<", 1) && r.redir[1] == '\0')
		new = set_in(r, doors);
    else if (!ft_strncmp(r.redir, ">>", 2) && r.redir[2] == '\0')
		new = set_out_d(r, doors);
    else if (!ft_strncmp(r.redir, "<<", 2) && r.redir[2] == '\0')
		new = set_in_d_in_pipe(doors);
    else 
        new = doors;
    return (new);
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

void launch_multiple_redir_in_pipes(t_redir *r, t_tab *t, char **cmds)
{
    t_doors doors;
    char *newcmd;
    int i;

    i = 0;
    doors.in = STDIN_FILENO;
    doors.out = STDOUT_FILENO;
    while (cmds[i] != NULL)
    {
        doors = set_redir_in_pipe(r[i], doors);
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
        new = split_with_starting_cmd(token, cmd);
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
    new = malloc(sizeof(char *) * (len + 1));
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

void read_heredoc(char *cmd)
{
    char **newcmds;
    char **tmp;
    t_redir *r;
    int i;

    i = 0;
    tmp = add_to_tab(new_tab(), cmd);
    newcmds = one_redir_pro_cmd(tmp);
    r = stock_redir_infos(newcmds);
    while (newcmds[i] != NULL)
    {
        if (!ft_strncmp(r[i].redir, "<<", 2))
            break ;
        i++;
    }
    launch_heredoc(r[i].dest);
}

int is_heredoc(char *cmd)
{
	int		*nbr;

	nbr = check_redir(cmd, '<');
    return (nbr[1]);
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
    new = malloc(sizeof(char *) * (tab_len(oldtab) + 2));
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


int how_many_splits_r(char *str)
{
	int     nbr;
    int		*nbr1;
	int		*nbr2;

    nbr1 = check_redir(str, '>');
    nbr2 = check_redir(str, '<');
    nbr = nbr1[0] + nbr1[1] + nbr2[0] + nbr2[1];
    free(nbr1);
    free(nbr2);
	return (nbr);
}

char **split_out_r(char *str)
{
	char **new;
	int nbr;
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	start = 0;
	nbr = how_many_splits_r(str);
	new = malloc(sizeof(char *) * (nbr + 1));
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\0' && str[i] != '>' && str[i] != '<')
			i++;
		if (i > start)
		{
			new[j] = ft_strldup(&str[start], i - start + 1);
			j++;
		}
		if (str[i] == '<')
		{
            if (str[i + 1] == '<')
            {
			    new[j] = ft_strdup("<<");
                i++;
            }
            else
                new[j] = ft_strdup("<");
			j++;
		}
        else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
            {
			    new[j] = ft_strdup(">>");
                i++;
            }
            else
                new[j] = ft_strdup(">");
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

char **split_redirs_tp(t_tprint tp)
{
	int i;
	char **splitted;
	char **tmp;
	char **last;
	char *quoted;

	i = 0;
	last = new_tab();
	while (tp.tab[i] != NULL)
	{
		if((how_many_in_str(tp.tab[i], '>') > 0 || how_many_in_str(tp.tab[i], '<') > 0) && (tp.print[i + 1] == 2 || tp.print[i + 1] == 5) && ft_strlen(tp.tab[i]) > 1)
		{
			splitted = split_out_r(tp.tab[i]);
			tmp = tabjoin(last, splitted);
			tabfree(last);
			tabfree(splitted);
			last = tmp;
		}
		else
		{
			if ((tp.print[i + 1] == 1 || tp.print[i + 1] == 4) && i != 0)
				quoted = add_quotes(tp.tab[i], '\"');
			else if ((tp.print[i + 1] == 0 || tp.print[i + 1] == 3) && i != 0)
				quoted = add_quotes(tp.tab[i], '\'');
			else
				quoted = ft_strdup(tp.tab[i]);
			tmp = add_to_tab(last, quoted);
			tabfree(last);
			free(quoted);
			last = tmp;
		}
		i++;
	}
	tmp = add_to_tab(last, "");
	tabfree(last);
	last = tmp;
	last[tab_len(tmp) - 1] = NULL;
	return (last);
}

size_t	ft_len_s(char const *s1, char const *s2)
{
	size_t	len;

	len = (ft_strlen(s1) + ft_strlen(s2));
	if ((ft_strlen(s1) == 0) || (ft_strlen(s2) == 0))
		len = len - 1;
	return (len);
}

char	*ft_strjoin_sep(char const *s1, char const *s2, char sep)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_len_s(s1, s2);
	ptr = malloc (sizeof(char) * len + 2);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (i < (ft_strlen(s1) + ft_strlen(s2) + 1))
	{
		if (i <= ft_strlen(s1))
			ptr[i] = s1[j++];
        if (i == ft_strlen(s1))
			ptr[i] = sep;
		if (i > ft_strlen(s1))
			ptr[i] = s2[k++];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char **split_w_starting_cmd(char **tab)
{
    char **new;
    char **ttmp;
    char *str;
    char *newstr;
    char *tmp;
    char *tmp2;
    int i;

    i = 0;
    str = ft_strdup("");
    new = new_tab();
    while(tab[i] != NULL && !(tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
        && !(tab[i][0] == '>' && tab[i][1] == '>'  && ft_strlen(tab[i]) == 2)
        && !(tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
        && !(tab[i][0] == '<' && tab[i][1] == '<'  && ft_strlen(tab[i]) == 2))
    {
        if (*str != '\0')
            tmp = ft_strjoin(str, " ");
        else
            tmp = ft_strdup(str);
        tmp2 = ft_strjoin(tmp, tab[i]);
        free(tmp);
        free(str);
        str = tmp2;
        i++;
    }
    while (tab[i] != NULL)
    {
        tmp = ft_strjoin_sep(str, tab[i], ' ');
        i++;
        newstr = ft_strdup("");
        while(tab[i] != NULL && !(tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
            && !(tab[i][0] == '>' && tab[i][1] == '>'  && ft_strlen(tab[i]) == 2)
            && !(tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
            && !(tab[i][0] == '<' && tab[i][1] == '<'  && ft_strlen(tab[i]) == 2))
        {
            if (*newstr != '\0')
                tmp2 = ft_strjoin_sep(newstr, tab[i], ' ');
            else
                tmp2 = ft_strdup(tab[i]);
            free(newstr);
            newstr = tmp2;
            i++;
        }
        ttmp = add_to_tab(new, ft_strjoin_sep(tmp, newstr, ' '));
        tabfree(new);
        new = ttmp;
        free(tmp);
        free(newstr);
    }
    ttmp = add_to_tab(new, "");
	tabfree(new);
	new = ttmp;
	new[tab_len(ttmp) - 1] = NULL;
    return (new);
}

int is_redir_next(char **tab)
{
    int i;

    i = 0;
    while(tab[i] != NULL)
    {
        if ((tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
            || (tab[i][0] == '>' && tab[i][1] == '>'  && ft_strlen(tab[i]) == 2)
            || (tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
            || (tab[i][0] == '<' && tab[i][1] == '<'  && ft_strlen(tab[i]) == 2))
                return (1);
        i++;
    }
    return (0);
}

char **split_w_starting_redir(char **tab)
{
    char **next;
    char **new = NULL;
    char **ttmp;
    char *newstr;
    char *str;
    char *tmp;
    char *tmp2;
    int i;

    i = 0;
    next = tab;
    new = new_tab();
    while (is_redir_next(next) && next != NULL)
        next++;
    if (next != NULL)
        next++;
    str = ft_strdup("");
    while (next[i] != NULL)
    {
        if (*str != '\0')
            tmp = ft_strjoin(str, " ");
        else
            tmp = ft_strdup(str);
        tmp2 = ft_strjoin(tmp, next[i]);
        free(tmp);
        free(str);
        str = tmp2;
        i++;
    }

    i = 0;
    while (tab[i] != NULL && is_redir_next(&tab[i]))
    {
        tmp = ft_strjoin_sep(str, tab[i], ' ');
        i++;
        newstr = ft_strdup("");
        while(tab[i] != NULL && is_redir_next(&tab[i - 1]) && !(tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
            && !(tab[i][0] == '>' && tab[i][1] == '>'  && ft_strlen(tab[i]) == 2)
            && !(tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
            && !(tab[i][0] == '<' && tab[i][1] == '<'  && ft_strlen(tab[i]) == 2))
        {
            if (*newstr != '\0')
                tmp2 = ft_strjoin_sep(newstr, tab[i], ' ');
            else
                tmp2 = ft_strdup(tab[i]);
            free(newstr);
            newstr = tmp2;
            i++;
        }
        ttmp = add_to_tab(new, ft_strjoin_sep(tmp, newstr, ' '));
        tabfree(new);
        new = ttmp;
        free(tmp);
        free(newstr);
    }
    ttmp = add_to_tab(new, "");
	tabfree(new);
	new = ttmp;
	new[tab_len(ttmp) - 1] = NULL;
    return (new);
}

char **a_redir_pro_cmd(char *cmd)
{
    t_tprint tp;
    char **splitted;
    char **new;

    tp = parsing_master(cmd);
    splitted = split_redirs_tp(tp);
    if (!ft_strncmp(splitted[0], ">", 1) || !ft_strncmp(splitted[0], "<", 1))
        new = split_w_starting_redir(splitted);
    else
        new = split_w_starting_cmd(splitted);
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
        launch_redir_in_pipe(r[0], t, newcmds[0]);
    }
    else if (nbr_of_redir(cmd) > 1)
    {
        newcmds = a_redir_pro_cmd(cmd);
        r = stock_redir_infos(newcmds);
        len = tab_len(newcmds);
        launch_multiple_redir_in_pipes(r, t, newcmds);
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
        newcmds = a_redir_pro_cmd(p.cmds[0]);
        r = stock_redir_infos(newcmds);
        len = tab_len(newcmds);
        launch_multiple_redir(r, t, newcmds);
    }
    else
        launch_pipes_with_redir(p, t);
}
