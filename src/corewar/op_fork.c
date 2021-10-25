/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 14:43:40 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 22:01:31 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		insert_new_process(t_vm *vm, t_process *new)
{
	t_process *list;

	list = vm->process_list;
	new->next = list;
	vm->process_list = new;
}

static void		fork_option(t_vm *vm, t_process *process,
		short index, short new_index)
{
	int		i;

	i = 0;
	if (vm->option_v[2])
	{
		ft_printf("P %4d | ", process->number);
		if (process->running == LFORK)
			ft_printf("l");
		ft_printf("fork %d (%d)\n", index, new_index);
	}
	if (vm->option_v[4])
	{
		ft_printf("ADV 3 (0x%.4x -> 0x%.4x)", process->program_counter,
				process->program_counter + 3);
		while (i < 3)
		{
			ft_printf(" %.2x",
					vm->arena[(process->program_counter + i) % MEM_SIZE]);
			i++;
		}
		ft_putendl(" ");
	}
	if (vm->option_v[5])
		ft_putstr(_END);
}

static void		fork_utils(t_process *new_process, t_process *process,
		short new_index)
{
	new_process->program_counter = new_index % MEM_SIZE;
	new_process->running = -1;
	new_process->cycles_to_wait--;
	process->is_fork = TRUE;
}

int				op_fork(t_vm *vm, t_process *process)
{
	t_process	*new_process;
	short		index;
	short		new_index;
	int			pc;

	pc = process->program_counter;
	if (vm->option_v[5])
		ft_putstr(_BLUE);
	index = vm->arena[(process->program_counter + 2) % MEM_SIZE];
	index += vm->arena[(process->program_counter + 1) % MEM_SIZE] * 16 * 16;
	if (!(new_process = (t_process*)malloc(sizeof(t_process))))
		exit_error(ERROR_MALLOC);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->number = vm->last_process_number + 1;
	vm->last_process_number = new_process->number;
	insert_new_process(vm, new_process);
	if (process->running == LFORK)
		new_index = pc + index;
	else
		new_index = pc + (index % IDX_MOD);
	fork_utils(new_process, process, new_index);
	fork_option(vm, process, index, new_index);
	return (process->program_counter + 3);
}
