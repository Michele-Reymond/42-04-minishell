/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/28 11:11:59 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include "libft/libft.h"

// __________ Macros __________
# define MINISHELL "minishell: "
# define ERROR_UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define ERROR_QUOTES "minishell: Unclosed quotes\n"
# define ERROR_ARGC "minishell: No arguments expected\n"
# define ERROR_CMD_NOT_FOUND "Command not found\n"
# define ERROR_FILE "No such file or directory\n"
# define EXIT "exit\n"
# define ERRORS_EXIT "exit: "
# define ERRORS_EXIT_ARGS "too many arguments\n"
# define ERRORS_NUM "numeric argument required\n"

// ______ Global variable_______
int	exit_status;

// ________ Structures _________
typedef struct s_echo {
	unsigned int	nbr_args;
	char			flag;
	char			**args;
	char			**vars;
}	t_echo;

typedef struct s_tprint {
	char	**tab;
	int		*print;
}	t_tprint;

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
	int 	e_status;
	t_parse	p;
}	t_tab;

// ________ Prototypes _________

//			Global
int			monitor(char *cmd, t_tab *t);
int			launch_cmds(char *cmd, t_tab *t);
int			is_a_builtin(char *cmd);
int			launch_builtins_with_redir(char *cmd, t_tab *t, int fd, int std);
int			launch_builtins_with_doors(char *cmd, t_tab *t, t_doors doors);
void		rl_replace_line (const char *text, int clear_undo);
void		rl_redisplay (void);
char		**tokenize(char *buff);

//			Parsing utils
int			how_many_in_str(char *str, char c);
int			how_many_in_tab(char **str, char c);
int			pre_parsing_errors(char *cmd, t_parse p);
t_parse		stock_parsing_infos(t_tprint tp);
char		**clean_cmds(char *cmd, t_parse p);
char		**clean_spaces(char *cmd);
char		**clean_quotes(char **cmds, t_parse p);
char		**clean_quotes_token(char **token, t_parse p);
t_tprint	parsing_master(char *cmd);
void		display_tab_and_int(int *inttab, char **tab);
void		display_inttab(int *inttab);

//			errors
void		check_args(int argc);

//			Builtins - cd
t_tab		*ms_b_cd(char *buf,t_tab *t);

//			Builtins - pwd
int			ms_b_pwd(void);

//			Builtins - echo
void		echo(t_tprint tp, t_tab t);
void		echo_print(char **args, char **var, int *print);
char		**echo_vars(char **tab, t_tab t, int nbr, int *print);
t_echo		echo_parsing(char **tab, t_tab t, int *print);
char		**clean_cmd_for_echo(char *cmd, t_tab *t);

//			Builtins - export
t_tab		*ft_export(t_tab *t, char **token);
void		display_export(char **env);
char		**make_export(char **env);

//			Builtins - unset

//			Builtins - env
char		**sort(char **env);
char		**update_env(char **old, t_var var, bool quotes);
char		**sort_env(char **env);
void		display_env(char **tab);

//			Builtins - exit
void		ft_exit(char *cmds, t_tab *t);
char		*replace_exit_status(char **token);
// char		**exit_status_convert(char **token);
char		*exit_status_convert(char *cmd);

//			Pipes
void		launch_with_pipes(t_parse p, t_tab *t);

//			Redirections
int			*check_redir(char *cmd, char redir);
void		launch_pipes_with_redir(t_parse p, t_tab *t);
void	    launching_redirs(char *cmd, t_tab *t);
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
char		**one_redir_pro_cmd(char **oldcmds);

//			Bin
int			ms_b_other(char *buf);
void		test_other(char *buf, t_tab *t, int fd, int std);
void		other_basic(char *buf, t_tab *t);
void		other_with_fork(char *buf, t_tab *t);
void		other_redir_and_fork(char *buf, t_tab *t, int fd, int std);
void		other_doors_and_fork(char *buf, t_tab *t, t_doors doors);

//			Variables
t_var		str_to_var(char *str);
char		**update_var(char **old, t_var var, int pos, bool quotes);
char		**update(char **old, t_var *var);
char		*var_to_str(t_var var);
char		*var_to_str_with_quotes(t_var var);
int			var_exist(char **env, char *var);
char		**add_var(char **old, t_var var, bool quotes);
char		**remove_var(char **old, char *key);
t_tab		*unset_var(t_tab *t, char **token);

//			Tables
char		**tabdup(char **tab);
void		tabfree(char **tab);
int			tab_len(char **tab);
char		*tab_to_str(char **token);
char		**tabsort(char **tab);
void		display_tab(char **tab);
char		**new_tab(void);
char		**add_to_tab(char **oldtab, char *str_to_add);
char		**tabjoin(char **tab1, char **tab2);

//			Signaux
void    	signal_handler(void);

//			à checker si utilisé
void		display(char **env);

#endif
