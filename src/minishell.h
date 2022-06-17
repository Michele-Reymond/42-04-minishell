/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/17 10:35:55 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"

# define ERROR_UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define ERROR_QUOTES "minishell: unclosed quotes\n"
# define ERROR_ARGC "minishell: No arguments expected\n"

typedef struct s_echo {
	unsigned int	nbr_args;
	char			flag;
	char			**args;
	char			**vars;
}	t_echo;

typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;

typedef struct s_doors
{
	int in;
	int out;
}	t_doors;

typedef struct s_ms_b_cd
{
	char	*param;
	char	*home;
	int		len;
	int		pos_buf;
	int		pos_param;
}	t_ms_b_cd;

typedef struct s_parse
{
	int		pipes;
	int		nbr_cmd;
	int		single_q;
	int		double_q;
	int		dollar;
	int		redir;
	int		redir_out;
	int		redir_in;
	int		redir_out_d;
	int		redir_in_d;
	char	**cmds;
}	t_parse;
// >	redirection de sortie
// <	redirection d'entree

typedef struct s_redir
{
	int		index;
	char	*dest;
	char	*redir;
	char	*cmd;
}	t_redir;

typedef struct s_tab
{
	char	**env;
	char	**exp;
	char	**var;
	char	**token;
	t_parse	p;
}	t_tab;

void		echo_print(char **args, char **var);
int			echo(char **token, t_tab t);
char		**echo_vars(char **token, t_tab t, int nbr);
t_echo		echo_parsing(char **token, t_tab t);
t_tab		*ft_export(t_tab *t, char **token);
char		**sort(char **env);
void		display(char **env);
t_var		str_to_var(char *str);
char		**update(char **old, t_var *var);
char		**update_var(char **old, t_var var, int pos, bool quotes);
char		**update_env(char **old, t_var var, bool quotes);
void		display_export(char **env);
char		**tabdup(char **tab);
void		tabfree(char **tab);
int			tab_len(char **tab);
char		*tab_to_str(char **token);
char		*var_to_str(t_var var);
char		*var_to_str_with_quotes(t_var var);
int			var_exist(char **env, char *var);
char		**add_var(char **old, t_var var, bool quotes);
char		**remove_var(char **old, char *key);
t_tab		*unset_var(t_tab *t, char **token);
char		**sort_env(char **env);
char		**tabsort(char **tab);
void		display_env(char **tab);
void		display_tab(char **tab);
char		**new_tab(void);
int			launch_cmds(char *cmd, t_tab *t);
int			is_a_builtin(char *cmd);
int			launch_builtins_with_redir(char *cmd, t_tab *t, int fd, int std);
int			launch_builtins_with_doors(char *cmd, t_tab *t, t_doors doors);
int			ms_b_pwd(void);
t_tab		*ms_b_cd(char *buf,t_tab *t);
int			ms_b_other(char *buf);
void		rl_replace_line (const char *text, int clear_undo);
void		rl_redisplay (void);
char		**tokenize(char *buff);
int			how_many_in_str(char *str, char c);
int			how_many_in_tab(char **str, char c);
int			monitor(char *cmd, t_tab *t);
int			pre_parsing_errors(char *cmd, t_parse p);
t_parse		stock_parsing_infos(char *cmd);
int			*check_redir(char *cmd, char redir);
char		**clean_cmds(char *cmd, t_parse p);
char		**clean_spaces(char *cmd);
char		**clean_quotes(char **cmds, t_parse p);
char		**clean_quotes_token(char **token, t_parse p);
char		**make_export(char **env);
void		check_args(int argc);
void		launch_with_pipes(t_parse p, t_tab *t);
void		launch_pipes_with_redir(t_parse p, t_tab *t);
void	    launching_redirs(char *cmd, t_tab *t);
void		test_other(char *buf, t_tab *t, int fd, int std);
void		other_basic(char *buf, t_tab *t);
void		other_with_fork(char *buf, t_tab *t);
void		other_redir_and_fork(char *buf, t_tab *t, int fd, int std);
void		other_doors_and_fork(char *buf, t_tab *t, t_doors doors);
void		launch_with_redir(t_parse p, t_tab *t);
void    	which_redir(t_redir *r, char *cmd);
char    	*stock_cmd_part(char **token, int pos);
char		**rebuilt_cmds(t_redir *r, int len);
t_redir		*stock_redir_infos(char **cmds);
void		launch_redir(t_redir r, t_tab *t, char *cmd);
void		launch_in_d(t_redir r, t_tab *t, char *cmd);
void		launch_in(t_redir r, t_tab *t, char *cmd);
void		launch_out_d(t_redir r, t_tab *t, char *cmd);
void		launch_out(t_redir r, t_tab *t, char *cmd);
int			is_heredoc(char *cmd);
void		read_heredoc(char *cmd);
char		**add_to_tab(char **oldtab, char *str_to_add);
char		**one_redir_pro_cmd(char **oldcmds);

#endif
