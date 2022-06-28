/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:20:52 by mreymond          #+#    #+#             */
/*   Updated: 2022/06/06 12:29:55 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args(int argc)
{
	if (argc > 1)
	{
		printf(ERROR_ARGC);
		exit(EXIT_FAILURE);
	}
}