/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:13:46 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/13 21:51:51 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*tokenize_string2(t_lexing *s, char *line, char *end, t_token *t)
{
	char	*new;

	if (end - s->column != line)
	{
		if (!(new = ft_strdup(end - s->column)))
			exit_error(ERROR_MALLOC);
		ft_strdel(&line);
		line = new;
	}
	s->column++;
	add_token(&s->tokens, t);
	return (line);
}

static char	*tokenize_string(t_lexing *s, char *line, size_t start, t_token *t)
{
	char	*end;
	char	*next_line;
	int		ret;
	size_t	i;

	ret = 1;
	while (!(end = ft_strchr(&line[start + 1], '\"'))
			&& (ret = get_next_line(s->fd, &next_line)) > 0)
		line = ft_strjoin_free(line, next_line);
	s->column++;
	i = s->column;
	while (line[i] != '\0' && line[i] != '\"')
	{
		s->column = (line[i] == '\n') ? 0 : s->column + 1;
		s->line = (line[i] == '\n') ? s->line + 1 : s->line;
		i++;
	}
	if (ret == FAILURE)
		exit_error(ERROR_READ_FILE);
	if (ret == 0)
		exit_lexical_error(s, line);
	t->column = start;
	if (!(t->content = ft_strsub(line, start, end + 1 - &line[start])))
		exit_error(ERROR_MALLOC);
	return (tokenize_string2(s, line, end, t));
}

static void	tokenize(t_lexing *s, char *line, size_t start, t_token *t)
{
	t->column = start;
	while (line[s->column] != '\0' && ft_strchr(LABEL_CHARS, line[s->column]))
		s->column++;
	if (s->column != start && line[s->column] == LABEL_CHAR
		&& t->type != INDIRECT_LABEL)
	{
		s->column++;
		if (!(t->content = ft_strsub(line, start, s->column - start)))
			exit_error(ERROR_MALLOC);
		t->type = LABEL;
		add_token(&s->tokens, t);
	}
	else if (s->column != start && (is_delimiter(line[s->column])
			|| (line[s->column] == '-' || ft_isdigit(line[s->column]))))
	{
		if (!(t->content = ft_strsub(line, start, s->column - start)))
			exit_error(ERROR_MALLOC);
		add_token(&s->tokens, t);
		if (t->type == INDIRECT)
			t->type = (is_register(t->content)) ? REGISTER : INSTRUCTION;
	}
	else
		exit_lexical_error(s, line);
}

static void	tokenize2(t_lexing *s, char *line, size_t start, t_token *t)
{
	size_t	start2;

	t->column = start;
	if (line[s->column] == '-')
		s->column++;
	start2 = s->column;
	if (s->column)
	{
		while (ft_isdigit(line[s->column]) == TRUE)
			s->column++;
	}
	if (s->column != start2 && (t->type == DIRECT
				|| (t->type == INDIRECT && is_delimiter(line[s->column]))))
	{
		if (!(t->content = ft_strsub(line, start, s->column - start)))
			exit_error(ERROR_MALLOC);
		add_token(&s->tokens, t);
	}
	else if (t->type == DIRECT)
	{
		s->column--;
		exit_lexical_error(s, line);
	}
	else if (t->type == INDIRECT)
		tokenize(s, line, s->column, t);
}

char		*lex_line(t_lexing *s, char *line)
{
	if (*(line + s->column) == SEPARATOR_CHAR)
		add_token(&s->tokens, create_token(s, SEPARATOR));
	else if (*(line + s->column) == '\n')
		add_token(&s->tokens, create_token(s, ENDLINE));
	else if (*(line + s->column) == '\"')
		line = tokenize_string(s, line, s->column, create_token(s, STRING));
	else if (*(line + s->column) == '.')
	{
		if (is_header_lexing_finished(s) == TRUE)
			exit_lexical_error(s, line);
		tokenize(s, line, s->column, create_token(s, COMMAND));
	}
	else if (*(line + s->column) == LABEL_CHAR)
		tokenize(s, line, s->column, create_token(s, INDIRECT_LABEL));
	else if (*(line + s->column) == DIRECT_CHAR
			&& *(line + s->column + 1) == LABEL_CHAR)
		tokenize(s, line, s->column, create_token(s, DIRECT_LABEL));
	else if (*(line + s->column) == DIRECT_CHAR
			&& *(line + s->column + 1) != LABEL_CHAR)
		tokenize2(s, line, s->column, create_token(s, DIRECT));
	else
		tokenize2(s, line, s->column, create_token(s, INDIRECT));
	return (line);
}
