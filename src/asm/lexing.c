/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:10:32 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/13 16:57:49 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_lexing(t_lexing *s)
{
	s->line = 0;
	s->column = 0;
	s->labels = NULL;
	s->tokens = NULL;
}

void		lex_source_code(t_lexing *s)
{
	int		ret;
	char	*line;

	init_lexing(s);
	while ((ret = get_next_line(s->fd, &line)) > 0)
	{
		s->line++;
		s->column = 0;
		while (line[s->column] != '\0')
		{
			while (ft_iswhitespace(line[s->column]) == TRUE)
				s->column++;
			if (line[s->column] == COMMENT_CHAR
				|| line[s->column] == ALT_COMMENT_CHAR)
				while (line[s->column] && line[s->column] != '\n')
					s->column++;
			if (line[s->column] != '\0')
				line = lex_line(s, line);
		}
		ft_strdel(&line);
	}
	(ret == FAILURE || s->line == 0) ? exit_error(ERROR_READ_FILE) : TRUE;
	ft_strdel(&line);
	get_next_line(CLEANUP, NULL);
	add_token(&s->tokens, create_token(s, END));
}
