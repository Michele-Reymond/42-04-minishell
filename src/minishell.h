/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/26 16:29:34 by mreymond         ###   ########.fr       */
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
# define ERRORS_EXP "export: "
# define ERRORS_UNSET "unset: "
# define ERRORS_EXIT_ARGS "too many arguments\n"
# define ERRORS_NUM "numeric argument required\n"
# define ERRORS_IDENTIFIER "not a valid identifier\n"
// # define NULL 0

// ______ Global variable_______
int	g_exit_status;

// ________ Structures _________
// parsing de echo
typedef struct s_echo {
	unsigned int	nbr_args;
	char			flag;
	char			**args;
	int				*spaces;
	char			**vars;
}	t_echo;

// tableau de str et indice pour 
// déterminer les quotes et espaces
typedef struct s_tprint {
	char	**tab;
	int		*print;
}	t_tprint;

// variables
typedef struct s_var
{
	char	*key;
	char	*value;
	int		status;
}	t_var;

// porte d'entrée et de sortie
typedef struct s_doors
{
	int	in;
	int	out;
}	t_doors;

// coordonnées d'un tableaux de char
typedef struct s_c
{
	int	i;
	int	j;
}	t_c;

typedef struct s_ms_b_cd
{
	char	*param;
	char	*home;
	int		len;
	int		pos_buf;
	int		pos_param;
}	t_ms_b_cd;

// parsing infos
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

// redirections infos
typedef struct s_redir
{
	int		index;
	char	*dest;
	char	*redir;
	char	*cmd;
}	t_redir;

// tableaux utils dans tous minishell
typedef struct s_tab
{
	char	**env;
	char	**exp;
	t_parse	p;
}	t_tab;

// ________ Prototypes _________

//			Global
int			monitor(char *cmd, t_tab *t);
int			launch_cmds(char *cmd, t_tab *t);
int			is_a_builtin(char *cmd);
int			launch_builtins_with_redir(char *cmd, t_tab *t, int fd, int std);
int			launch_builtins_with_doors(char *cmd, t_tab *t, t_doors doors);
void		rl_replace_line(const char *text, int clear_undo);
void		rl_redisplay(void);
char		**tokenize(char *buff);

//			Parsing
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
char		*ft_strldup(const char *src, size_t dstsize);
int			check_identifier(char *str);
char		*add_quotes(char *old, char quote);
char		*join_strings(t_tprint tp, int pos, int start);
int			check_closed_quotes(t_tprint tp);
char		**split_pipes(t_tprint tp, int pipes);
void		copy_outside_quotes(char *cmd, int *i, int *j, t_tprint new);
int			copy_inside_quotes(char *cmd, t_c *c, char *stock, t_tprint new);
int			count_quotes(char *cmd, char stock, int i);
void		trim_single_and_tprint(t_tprint tmp, t_tprint *tp, int i);
void		trim_doubles_and_tprint(t_tprint tmp, t_tprint *tp, int i);
void		trim_and_tprint_else(t_tprint tmp, t_tprint *tp, int i);
int			how_many_splits(char *str);
char		*adding_quotes(t_tprint tp, int i);
int			count_pipes(t_tprint tp);
int			count_doubles(t_tprint tp);
int			count_singles(t_tprint tp);
int			count_dollar(t_tprint tp);
void		count_redir(t_tprint tp, t_parse *p);

//			errors
void		check_args(int argc);

//free
void		ft_free(char *str);
void		free_tabs(t_tab *t, char **tab);
void		free_t_tab(t_tab *t);
void		free_tp(t_tprint tp);
int			free_tp_status_error(t_tprint tp);
void		free_elem(t_echo elem);
void		free_vartab(t_var *vartab, int len);
void		free_t_redirs(t_redir r);
void		free_redirs(int *nbr1, int *nbr2);
void		free_all_t_redirs(t_redir *r, int len);

//			Builtins - cd
//t_tab		*ms_b_cd(char *buf,t_tab *t);
t_tab		*ms_b_cd(t_tprint tp, t_tab *t);

//			Builtins - pwd
int			ms_b_pwd(void);

//			Builtins - echo
void		echo(t_tprint tp, t_tab t);
void		echo_print(char **args, char **var, int *print);
char		**echo_vars(char **tab, t_tab t, int nbr, int *print);
t_echo		echo_parsing(char **tab, t_tab t, int *print);
char		**clean_cmd_for_echo(char *cmd, t_tab *t);
char		*copy_variables(char *tmp, char **vars, int j, t_tab t);
int			*copy_spaces_tab(int *print);
int			how_many_dollars(char **tab, int *print);

//			Builtins - export and unset
t_tab		*ft_export(t_tab *t, t_tprint tp);
void		display_export(char **env);
char		**make_export(char **env);
char		**parsing_for_export(t_tprint tp);
int			spaces_count(t_tprint tp);
t_tab		*unset(t_tab *t, t_tprint tp);
t_var		*create_vartab(int *i, char **token);
void		update_with_new_var(t_tab *t, t_var var, int *i, int *j);
void		export_errors(t_var var, int *i, int *j);
void		export_increase(int *i, int *j);

//			Builtins - env
char		**sort(char **env);
char		**update_env(char **old, t_var var, bool quotes);
char		**sort_env(char **env);
void		display_env(char **tab);

//			Builtins - exit
void		ft_exit(char *cmds, t_tab *t);
char		*replace_exit_status(char **token);
char		*exit_status_convert(char *cmd, char *symbol);
long long	ft_atoll(const char *str);
int			args_if_alpha(char *str);

//			Pipes
void		launch_with_pipes(t_parse p, t_tab *t);
int			count_multi_pipes_cmds(t_tprint tp);
int			multipipes_split(t_tprint tp, t_tprint *last, int i, int j);
int			onepipes_split(t_tprint tp, t_tprint *last, int i, int j);
void		create_pipes(int **fd, int nbr);
void		launching_pipes_in_child(t_parse p, t_tab *t, pid_t *pid, int **fd);
void		launching_pipes_in_parent(t_parse p, pid_t *pid, int **fd);
void		check_files_needs(char *cmd);
void		child_process(int **fd, int pos, int nbr);
void		closing_loop_in(int **fd, int pos, int nbr);
void		closing_loop_out(int **fd, int pos, int nbr);
void		parent_closing_loop(int **fd, int nbr);

//			Redirections
int			*check_redir(char *cmd, char redir);
void		launch_pipes_with_redir(t_parse p, t_tab *t);
void		launching_redirs(char *cmd, t_tab *t);
void		launch_with_redir(t_parse p, t_tab *t);
void		which_redir(t_redir *r, char *cmd);
char		*stock_cmd_part(char **token, int pos);
char		**rebuilt_cmds(t_redir *r, int len);
t_redir		*stock_redir_infos(char **cmds);
void		launch_redir(t_redir r, t_tab *t, char *cmd);
void		launch_in_d(t_redir r, t_tab *t, char *cmd);
void		launch_in(t_redir r, t_tab *t, char *cmd);
void		launch_out_d(t_redir r, t_tab *t, char *cmd);
void		launch_out(t_redir r, t_tab *t, char *cmd);
int			is_heredoc(char *cmd);
void		read_heredoc(char *cmd);
char		**a_redir_pro_cmd(char *cmd);
t_redir		dup_redir(t_redir r);
int			redir_errors(int *nbr1, int *nbr2, t_parse *p);
void		init_redirections(t_parse *p);
t_doors		set_redirection(t_redir r, t_doors doors);
t_doors		set_redir_in_pipe(t_redir r, t_doors doors);
void		launch_child_in_set(t_redir r, int tmpfile);
t_doors		init_doors(void);
int			nbr_of_redir(char *cmd);
void		launch_redir_in_pipe(t_redir r, t_tab *t, char *cmd);
char		*ft_strjoin_sep(char const *s1, char const *s2, char sep);
char		*find_cmd(char **tab);
char		*join_cmd(char *cmd, char *next);
char		**split_out_r(char *str);
char		**split_w_starting_redir(char **tab);
char		**split_w_starting_cmd(char **tab);
void		launch_heredoc(char *stop);
void		pid_errors(pid_t pid);
void		launch_in_d_in_pipe(t_tab *t, char *cmd);
void		launch_in_basic(t_redir r, t_tab *t, char *cmd);
void		check_files_out(char *file);
void		check_files_in(char *file);
int			check_files_in_basic(char *file);
int			check_files_out_basic(char *file);
void		fork_and_launch_builtin(char *cmd, t_tab *t, int fd, int std);
void		parse_for_redir_infos(char *cmd, t_redir *r, int index);
t_doors		set_out(t_redir r, t_doors doors);
t_doors		set_out_d(t_redir r, t_doors doors);
t_doors		set_in(t_redir r, t_doors doors);
t_doors		set_in_d(t_redir r, t_doors doors);
t_doors		set_in_d_in_pipe(t_doors doors);
int			is_redir_next(char **tab);

//			Bin
int			ms_b_other(char *buf);
void		test_other(char *buf, t_tab *t, int fd, int std);
void		other_basic(char *buf, t_tab *t);
void		other_with_fork(char *buf, t_tab *t);
void		other_redir_and_fork(char *buf, t_tab *t, int fd, int std);
void		other_doors_and_fork(char *buf, t_tab *t, t_doors doors);
void		status_of_child(int status);
void		launch_child_process(char *buff, char **paths, char **envp);

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
void		signal_handler(void);
void		rl_replace_line(const char *text, int clear_undo);

#endif
