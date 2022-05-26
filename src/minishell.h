/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/26 16:31:08 by mreymond         ###   ########.fr       */
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

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

void		echo_print(char **args, char **var);
int			echo(t_echo elem);
void		ft_export(char **env, t_env_var new_var);
char		**sort_env(char **env);
void		display_env(char **env);
t_env_var	str_to_var(char *str);
char		**update_env(char **old, t_env_var *var);
char		**update_var(char **old, t_env_var *var, int pos);
void		display_export(char **env);
char		**tabdup(char **tab);

#endif

// liste des malloc à free à la fin :
// - dans la fonction sort_env