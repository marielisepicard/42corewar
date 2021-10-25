/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:10:32 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/25 11:07:15 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_tokens(t_token **list)
{
	t_token	*curr;
	t_token	*delete;

	curr = *list;
	while (curr)
	{
		delete = curr;
		curr = curr->next;
		ft_strdel(&(delete->content));
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void	free_mentions(t_mention **list)
{
	t_mention	*curr;
	t_mention	*delete;

	curr = *list;
	while (curr)
	{
		delete = curr;
		curr = curr->next;
		ft_strdel(&(delete->token_content));
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void	free_labels(t_label **list)
{
	t_label	*curr;
	t_label	*delete;

	curr = *list;
	while (curr)
	{
		delete = curr;
		curr = curr->next;
		ft_strdel(&(delete->name));
		free_mentions(&(delete->mentions));
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void	free_s(t_lexing *s, t_parsing *p)
{
	free_tokens(&s->tokens);
	free_labels(&s->labels);
	ft_strdel(&p->code);
}
