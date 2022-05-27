/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroch <vroch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:16:50 by vroch             #+#    #+#             */
/*   Updated: 2022/05/27 13:53:05 by vroch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* **************************************************************************
 *  parameter : none
 */

int	ms_b_pwd(void)
{
	char	*home;

	home = getenv("HOME");
	ft_putendl_fd(home, 2);
	return (0);
 *  parameter : arg = full line from readline.
 *  no action on buf
 *   
 */
int ms_b_pwd(void)
{
	char	*home;
	
	home = getenv("HOME");
	
	ft_putendl_fd(home, 2);
    return (0);
}
