/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 17:05:04 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"


typedef struct s_echo {
	char			*cmd;
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

typedef struct s_tab
{
	char	**env;
	char	**exp;
	char	**var;
}	t_tab;

typedef struct s_ms_b_cd
{
	char	*param;
	char	*home;
	int		len;
	int		pos_buf;
	int		pos_param;
}	t_ms_b_cd;

void		echo_print(char **args, char **var);
int			echo(t_echo elem);
void		ft_export(char **env, t_var *var);
char		**sort(char **env);
void		display(char **env);
t_var		str_to_var(char *str);
char		**update(char **old, t_var *var);
char		**update_var(char **old, t_var *var, int pos);
void		display_export(char **env);
char		**tabdup(char **tab);
void		tabfree(char **tab);
int			tab_len(char **tab);
char		*var_to_str(t_var *var);
int			var_exist(char **env, char *var);
char		**add_var(char **old, t_var *var);
char		**remove_var(char **old, t_var *var);
char		**sort_env(char **env);
void		display_tab(char **tab);
char		**new_tab(void);
int			launch_builtins(char *cmd, t_tab t);
int			ms_b_pwd(void);
int			ms_b_cd(char *buf);
int			ms_b_other(char *buf);
void		rl_replace_line (const char *text, int clear_undo);
void		rl_redisplay (void);

#endif

// liste des malloc à free à la fin :
// - dans la fonction sort_env