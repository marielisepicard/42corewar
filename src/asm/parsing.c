/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:21:59 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/28 11:25:34 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		replace_mentions(t_lexing *s, t_parsing *p)
{
	t_label		*l;
	t_mention	*m;

	l = s->labels;
	while (l)
	{
		if (l->op_pos == -1)
			exit_label_error(l);
		else
		{
			m = l->mentions;
			while (m)
			{
				int2byte(p->code, m->pos, l->op_pos - m->op_pos, m->size);
				m = m->next;
			}
		}
		l = l->next;
	}
}

static t_token	*parse_label(t_lexing *s, t_parsing *p, t_token *curr)
{
	t_label	*l;
	char	*name;

	if (!(name = ft_strsub(curr->content, 0, ft_strlen(curr->content) - 1)))
		exit_error(ERROR_MALLOC);
	if (!(l = find_label(s->labels, name)))
		add_label(&s->labels, create_label(name, p->op_pos));
	if (l && l->op_pos == -1)
		l->op_pos = p->pos;
	ft_strdel(&name);
	curr = curr->next;
	return (curr);
}

static t_op		*select_op(t_token *curr, t_parsing *p)
{
	t_op	*op;
	size_t	i;

	i = 0;
	op = NULL;
	while (i < (sizeof(g_op_tab) / sizeof(t_op)))
	{
		if (ft_strequ(g_op_tab[i].name, curr->content) == TRUE)
			op = &g_op_tab[i];
		i++;
	}
	(op == NULL) ? exit_token_error(curr->next) : TRUE;
	p->code[p->pos] = op->code;
	p->pos = (op->args_types_code == TRUE) ? p->pos + 2 : p->pos + 1;
	return (op);
}

static void		parse_asm_code(t_lexing *s, t_parsing *p, t_token *curr)
{
	while (curr->type != END)
	{
		if (p->pos >= p->code_size)
		{
			p->code_size += CHAMP_MAX_SIZE;
			if (!(p->code = (char *)realloc(p->code, p->code_size + 14)))
				exit_error(ERROR_MALLOC);
			ft_bzero(p->code + p->pos, p->code_size + 14 - p->pos);
		}
		p->op_pos = p->pos;
		if (curr->type == LABEL)
			curr = parse_label(s, p, curr);
		if (curr->type == INSTRUCTION)
			curr = parse_inst(s, p, curr, select_op(curr, p));
		if (curr->type != ENDLINE)
			exit_token_error(curr);
		curr = curr->next;
	}
	if (ft_strlen(p->code) == 0)
		exit_token_error(curr);
	replace_mentions(s, p);
}

void			parse_source_code(t_lexing *s, t_parsing *p)
{
	t_token *curr;

	curr = s->tokens;
	ft_bzero(p->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(p->comment, COMMENT_LENGTH + 1);
	p->pos = 0;
	p->op_pos = 0;
	p->code_size = 0;
	p->code = NULL;
	parse_header(p, &curr);
	parse_asm_code(s, p, curr);
	p->output_length = PROG_NAME_LENGTH + COMMENT_LENGTH + p->pos + 16;
}
