/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_lives2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:49:25 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 22:02:15 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			restore_live_calls(t_process *list)
{
	while (list)
	{
		list->live_calls = 0;
		list = list->next;
	}
}

int				count_live_calls(t_process *list)
{
	int	res;

	res = 0;
	while (list)
	{
		res = res + list->live_calls;
		list->live_calls = 0;
		list = list->next;
	}
	return (res);
}

void			fill_tab(int **tab, t_vm *vm)
{
	t_process	*tmp;
	int			i;

	tmp = vm->process_list;
	i = 0;
	while (tmp != NULL && i < 3)
	{
		if (!(tab[i] = (int *)malloc(sizeof(int) * 3)))
			exit_error(ERROR_MALLOC);
		tab[i][0] = tmp->number;
		tab[i][1] = tmp->since_last_live;
		if (vm->neg_ctd == 0)
			tab[i][2] = vm->delta_ctd;
		else
			tab[i][2] = vm->neg_ctd;
		tmp = tmp->next;
		i++;
	}
}
