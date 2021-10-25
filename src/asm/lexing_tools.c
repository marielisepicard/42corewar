/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:13:23 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/25 13:13:38 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int8_t	is_delimiter(char c)
{
	return (c == '\0'
			|| c == '\n'
			|| ft_iswhitespace(c)
			|| c == '.'
			|| c == '\"'
			|| c == DIRECT_CHAR
			|| c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR
			|| c == ALT_COMMENT_CHAR);
}

int8_t	is_register(char *arg)
{
	if (arg == NULL)
		return (FALSE);
	if (ft_strlen(arg) < 2 || ft_strlen(arg) > 3 || arg[0] != 'r')
		return (FALSE);
	if (ft_strlen(arg) == 2 && ft_isdigit(arg[1] == FALSE))
		return (FALSE);
	if (ft_strlen(arg) == 3
			&& (ft_isdigit(arg[1]) == FALSE || ft_isdigit(arg[2]) == FALSE))
		return (FALSE);
	return (TRUE);
}

int8_t	is_header_lexing_finished(t_lexing *s)
{
	t_token *t;
	int		commands;

	commands = 0;
	t = s->tokens;
	while (t != NULL)
	{
		if (t->type == COMMAND)
			commands++;
		t = t->next;
	}
	if (commands == 2)
		return (TRUE);
	return (FALSE);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*curr;

	if (*list != NULL)
	{
		curr = *list;
		while (curr->next != NULL)
			curr = curr->next;
		if (curr->type == ENDLINE && new->type == ENDLINE)
			ft_memdel((void **)&new);
		else
			curr->next = new;
	}
	else
	{
		if (new->type == ENDLINE)
			ft_memdel((void **)&new);
		else
			*list = new;
	}
}

t_token	*create_token(t_lexing *s, t_type type)
{
	t_token	*t;

	if (!(t = (t_token *)ft_memalloc(sizeof(t_token))))
	{
		exit_error(ERROR_MALLOC);
		return (NULL);
	}
	t->content = NULL;
	t->type = type;
	t->line = s->line;
	t->next = NULL;
	if (type == SEPARATOR
			|| type == ENDLINE
			|| type == COMMAND
			|| type == INDIRECT_LABEL
			|| type == DIRECT)
		s->column++;
	if (type == DIRECT_LABEL)
		s->column += 2;
	t->column = s->column;
	if (type == SEPARATOR)
		if (!(t->content = ft_strdup(",")))
			exit_error(ERROR_MALLOC);
	return (t);
}
