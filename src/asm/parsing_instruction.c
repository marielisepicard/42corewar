/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:21:59 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/26 18:41:29 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	process_instruct(t_lexing *s, t_parsing *p, t_token *curr, t_op *op)
{
	if (curr->type == INDIRECT_LABEL)
		add_ment(s, p, curr, IND_SIZE);
	else if (curr->type == DIRECT_LABEL)
		add_ment(s, p, curr, op->t_dir_size);
	else if (curr->type == INDIRECT)
		int2byte(p->code, p->pos, num(&curr->content[0]), IND_SIZE);
	else if (curr->type == DIRECT)
		int2byte(p->code, p->pos, num(&curr->content[1]), op->t_dir_size);
	else if (curr->type == REGISTER)
		int2byte(p->code, p->pos, num(&curr->content[1]), 1);
}

static void	update_code_pos(t_parsing *p, t_token *curr, t_op *op)
{
	if (curr->type == INDIRECT_LABEL)
		p->pos += IND_SIZE;
	else if (curr->type == DIRECT_LABEL)
		p->pos += op->t_dir_size;
	else if (curr->type == INDIRECT)
		p->pos += IND_SIZE;
	else if (curr->type == DIRECT)
		p->pos += op->t_dir_size;
	else if (curr->type == REGISTER)
		p->pos++;
}

static void	write_args_bytecode(t_parsing *p, t_token *curr, t_op *op, int8_t i)
{
	if (op->args_types_code == TRUE)
	{
		if (curr->type == INDIRECT_LABEL)
			p->code[p->op_pos + 1] |= IND_CODE << (6 - 2 * i);
		else if (curr->type == DIRECT_LABEL)
			p->code[p->op_pos + 1] |= DIR_CODE << (6 - 2 * i);
		else if (curr->type == INDIRECT)
			p->code[p->op_pos + 1] |= IND_CODE << (6 - 2 * i);
		else if (curr->type == DIRECT)
			p->code[p->op_pos + 1] |= DIR_CODE << (6 - 2 * i);
		else if (curr->type == REGISTER)
			p->code[p->op_pos + 1] |= REG_CODE << (6 - 2 * i);
	}
}

t_token		*parse_inst(t_lexing *s, t_parsing *p, t_token *curr, t_op *op)
{
	int8_t	i;

	i = 0;
	curr = curr->next;
	while (i < op->args_nb)
	{
		if (curr->type < REGISTER || curr->type > INDIRECT_LABEL)
			exit_token_error(curr);
		process_instruct(s, p, curr, op);
		update_code_pos(p, curr, op);
		write_args_bytecode(p, curr, op, i);
		if ((op->args_types[i] & get_arg_type(curr->type)) == FALSE)
			exit_arg_type_error(op, i, curr);
		curr = curr->next;
		if (i < op->args_nb - 1 && curr->type != SEPARATOR)
			exit_token_error(curr);
		if (i < op->args_nb - 1)
			curr = curr->next;
		i++;
	}
	return (curr);
}
