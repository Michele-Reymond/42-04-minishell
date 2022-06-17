/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:16:50 by vroch             #+#    #+#             */
/*   Updated: 2022/06/17 16:26:57 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* **************************************************************************
 *  parameter : none
 *   ces commandes semblent equivalentes: 	
 * 		pwd = getenv("PWD");
 *		pwd = getcwd(NULL, 0); + free
 */



int	ms_b_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 2);
	exit_status = 0;
	free(pwd);
	return (0);
}
