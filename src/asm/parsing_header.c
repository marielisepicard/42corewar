/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:21:59 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/26 18:40:41 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_cmd(t_parsing *p, t_token **curr, char *cmd, size_t max_len)
{
	*curr = (*curr)->next;
	if ((*curr)->type == STRING)
	{
		if (ft_strlen((*curr)->content) - 2 > max_len)
			exit_header_error(cmd);
		if (ft_strequ(NAME_CMD_STRING, cmd) == TRUE)
			ft_strncpy(p->prog_name, (*curr)->content + 1, max_len);
		if (ft_strequ(COMMENT_CMD_STRING, cmd) == TRUE)
			ft_strncpy(p->comment, (*curr)->content + 1, max_len);
		*curr = (*curr)->next;
	}
	else
		exit_token_error(*curr);
}

void		parse_header(t_parsing *p, t_token **curr)
{
	size_t i;

	while (p->prog_name[0] == '\0' || p->comment[0] == '\0')
	{
		if ((*curr)->type == COMMAND && p->prog_name[0] == '\0'
				&& ft_strequ((*curr)->content, NAME_CMD_STRING))
			parse_cmd(p, curr, NAME_CMD_STRING, PROG_NAME_LENGTH);
		else if ((*curr)->type == COMMAND && p->comment[0] == '\0'
				&& ft_strequ((*curr)->content, COMMENT_CMD_STRING))
			parse_cmd(p, curr, COMMENT_CMD_STRING, COMMENT_LENGTH);
		else
			exit_token_error(*curr);
		if ((*curr)->type != ENDLINE)
			exit_token_error(*curr);
		*curr = (*curr)->next;
	}
	i = 0;
	while (p->prog_name[i] != '\0')
		i++;
	(p->prog_name[i - 1] == '"') ? p->prog_name[i - 1] = 0 : 0;
	i = 0;
	while (p->comment[i] != '\0')
		i++;
	(p->comment[i - 1] == '"') ? p->comment[i - 1] = 0 : 0;
}
