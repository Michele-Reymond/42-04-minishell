/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/27 16:20:48 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"

# define ECHO	"echo"
# define CD		"cd"
# define PWD	"pwd"
# define EXPORT	"export"
# define UNSET	"unset"
# define ENV	"env"
# define EXIT	"exit"

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
	char	**token;
}	t_tab;

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
int			launch_builtins(char *cmd);
char		**tokenize(char *buff);
int			how_many_in_str(char *str, char c);
int			how_many_in_tab(char **str, char c);

#endif

// liste des malloc à free à la fin :
// - dans la fonction sort_env