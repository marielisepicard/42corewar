/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_lives.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:49:25 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 22:21:05 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		delete_link(t_vm *vm, t_process *to_del)
{
	t_process	*list;
	t_process	*previous;

	previous = NULL;
	list = vm->process_list;
	while (list)
	{
		if (list == to_del)
		{
			if (previous == NULL)
			{
				vm->process_list = list->next;
				free(list);
				return ;
			}
			else
			{
				previous->next = list->next;
				free(list);
				return ;
			}
		}
		previous = list;
		list = list->next;
	}
}

void			kill_all_cursors(t_vm *vm)
{
	t_process	*list;
	t_process	*tmp;

	list = vm->process_list;
	while (list)
	{
		tmp = list->next;
		if (vm->option_v[3])
		{
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						list->number, list->since_last_live,
						vm->delta_ctd_copy);
		}
		delete_link(vm, list);
		list = tmp;
	}
	if (vm->option_v[1])
	{
		if (vm->live_calls >= 21)
			ft_printf("Cycle to die is now %d\n", vm->delta_ctd_copy - 50);
	}
}

static void		print_dead_cursors(t_process *list, t_vm *vm)
{
	if (vm->neg_ctd == 0)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				list->number, list->since_last_live, vm->delta_ctd_copy);
	else
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				list->number, list->since_last_live, vm->neg_ctd);
}

void			kill_dead_cursors(t_vm *vm)
{
	t_process	*list;
	t_process	*tmp;

	list = vm->process_list;
	while (list)
	{
		tmp = list->next;
		if (list->live_calls <= 0)
		{
			if (vm->option_v[3])
				print_dead_cursors(list, vm);
			delete_link(vm, list);
		}
		list = tmp;
	}
}
