/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_asm2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:10:32 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/27 15:41:47 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void	exit_arg_type_error(t_op *op, int arg_num, t_token *t)
{
	ft_fdprintf(2, "Invalid parameter %d ", arg_num);
	ft_fdprintf(2, "type %s for instruction %s\n", g_type2[t->type], op->name);
	exit(EXIT_FAILURE);
}

void	exit_header_error(char *cmd)
{
	if (ft_strequ(cmd, NAME_CMD_STRING) == TRUE)
		ft_fdprintf(2, "Champion name too long (Max length %d)\n",
					PROG_NAME_LENGTH);
	if (ft_strequ(cmd, COMMENT_CMD_STRING) == TRUE)
		ft_fdprintf(2, "Champion comment too long (Max length %d)\n",
					COMMENT_LENGTH);
	exit(EXIT_FAILURE);
}
