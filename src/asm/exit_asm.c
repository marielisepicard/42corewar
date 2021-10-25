/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:10:32 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/07 12:24:47 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <errno.h>
#include <stdio.h>

void	exit_error(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit(EXIT_FAILURE);
}

void	exit_lexical_error(t_lexing *s, char *line)
{
	ft_strdel(&line);
	ft_fdprintf(2, "Lexical error at [%d:%d]\n", s->line, s->column + 1);
	exit(EXIT_FAILURE);
}

void	exit_token_error(t_token *t)
{
	if (t->type != ENDLINE && t->type != SEPARATOR)
		ft_fdprintf(2, "Syntax error at token [TOKEN][%03d:%03d] ",
					t->line, t->column + 1);
	else
		ft_fdprintf(2, "Syntax error at token [TOKEN][%03d:%03d] ",
					t->line, t->column);
	if (t->type == COMMAND && ft_strequ(t->content, ".name"))
		ft_fdprintf(2, "COMMAND_NAME \"%s\"\n", t->content);
	else if (t->type == COMMAND && ft_strequ(t->content, ".comment"))
		ft_fdprintf(2, "COMMAND_COMMENT \"%s\"\n", t->content);
	else if (t->type == ENDLINE)
		ft_fdprintf(2, "ENDLINE\n");
	else
		ft_fdprintf(2, "%s \"%s\"\n", g_type[t->type], t->content);
	exit(EXIT_FAILURE);
}

void	exit_label_error(t_label *l)
{
	t_mention	*m;

	m = l->mentions;
	ft_fdprintf(2, "No such label %s while attempting to dereference", l->name);
	ft_fdprintf(2, " token [TOKEN][%03d:%03d] %s \"%s\"\n", m->line,
				m->column + 1, g_type[m->token_type], m->token_content);
	exit(EXIT_FAILURE);
}

void	exit_instruction_error(t_token *t)
{
	ft_fdprintf(2, "Unknown instruction \"%s\"at [%d:%d]\n", t->content,
				t->line, t->column + 1);
	exit(EXIT_FAILURE);
}
