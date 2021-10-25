/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:21:59 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/25 14:06:02 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label		*find_label(t_label *l, char *name)
{
	t_label		*curr;

	curr = l;
	while (curr != NULL)
	{
		if (ft_strequ(curr->name, name) == TRUE)
			return (curr);
		curr = curr->next;
	}
	return (curr);
}

void		add_label(t_label **l, t_label *new)
{
	t_label		*curr;

	if (l != NULL && *l != NULL)
	{
		curr = *l;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else if (l != NULL)
		*l = new;
}

t_label		*create_label(char *name, ssize_t op_pos)
{
	t_label		*l;

	if (!(l = (t_label *)ft_memalloc(sizeof(t_label))))
	{
		exit_error(ERROR_MALLOC);
		return (NULL);
	}
	if (!(l->name = ft_strdup(name)))
		exit_error(ERROR_MALLOC);
	l->op_pos = op_pos;
	l->mentions = NULL;
	l->next = NULL;
	return (l);
}

void		add_ment(t_lexing *s, t_parsing *p, t_token *curr, int8_t size)
{
	char		*name;
	t_label		*l;
	t_mention	*curr2;
	t_mention	**m;

	name = (curr->type == INDIRECT_LABEL) ?
		ft_strsub(curr->content, 1, ft_strlen(curr->content) - 1)
		: ft_strsub(curr->content, 2, ft_strlen(curr->content) - 2);
	(name == NULL) ? exit_error(ERROR_MALLOC) : 0;
	if ((l = find_label(s->labels, name)) == NULL)
	{
		l = create_label(name, -1);
		add_label(&(s->labels), l);
	}
	ft_strdel(&name);
	m = &l->mentions;
	if (m != NULL && *m != NULL)
	{
		curr2 = *m;
		while (curr2->next)
			curr2 = curr2->next;
		curr2->next = create_mention(p, curr, size);
	}
	else if (m != NULL)
		*m = create_mention(p, curr, size);
}

t_mention	*create_mention(t_parsing *p, t_token *t, size_t size)
{
	t_mention	*m;

	if (!(m = (t_mention *)ft_memalloc(sizeof(t_mention))))
	{
		exit_error(ERROR_MALLOC);
		return (NULL);
	}
	m->line = t->line;
	m->column = t->column;
	m->pos = p->pos;
	m->op_pos = p->op_pos;
	m->size = size;
	m->token_type = t->type;
	if (!(m->token_content = ft_strdup(t->content)))
		exit_error(ERROR_MALLOC);
	m->next = NULL;
	return (m);
}
