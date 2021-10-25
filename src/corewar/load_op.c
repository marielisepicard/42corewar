/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:31:26 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 20:08:26 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	(*g_op_function[17])(t_vm *vm, t_process *p) =
{
	[LIVE] = &op_live,
	[LD] = &launch_ld,
	[ST] = &launch_st,
	[ADD] = &launch_add,
	[SUB] = &launch_sub,
	[AND] = &bite_op,
	[OR] = &bite_op,
	[XOR] = &bite_op,
	[ZJMP] = &op_zjmp,
	[LDI] = &launch_ldi,
	[STI] = &launch_sti,
	[FORK] = &op_fork,
	[LLD] = &launch_lld,
	[LLDI] = &launch_lldi,
	[LFORK] = &op_fork,
	[AFF] = &op_aff
};

static void	exec_operation(t_process *p, t_vm *vm)
{
	if (p->running > 0 && p->running <= 16)
		p->program_counter = (int)g_op_function[p->running](vm, p) % MEM_SIZE;
}

t_process	*no_current_op(t_vm *vm, int pc, t_process *tmp)
{
	if (vm->arena[pc] > 0 && vm->arena[pc] < 17)
	{
		tmp->running = vm->arena[pc];
		tmp->cycles_to_wait = get_cycle_to_wait(tmp->running);
	}
	else
	{
		tmp->program_counter++;
		tmp->program_counter = tmp->program_counter % MEM_SIZE;
	}
	return (tmp);
}

void		man_op(t_vm *vm, int cycle)
{
	if (vm->option_v[5])
		ft_putstr(_YELLOW);
	if (vm->option_v[1] && cycle > 0)
		ft_printf("It is now cycle %d\n", cycle);
}

void		load_operations(t_vm *vm, int cycle)
{
	t_process		*tmp;

	if (vm->option_v[5] || vm->option_v[1])
		man_op(vm, cycle);
	tmp = vm->process_list;
	while (tmp)
	{
		tmp->since_last_live++;
		if (tmp->program_counter < 0)
			tmp->program_counter = MEM_SIZE + (tmp->program_counter % MEM_SIZE);
		if (tmp->running == -1)
			tmp = no_current_op(vm, tmp->program_counter, tmp);
		if (tmp->running != -1 && cycle != 0)
		{
			tmp->cycles_to_wait--;
			if (tmp->cycles_to_wait == 0)
			{
				exec_operation(tmp, vm);
				tmp->running = -1;
			}
		}
		tmp = tmp->next;
	}
	if (vm->option_v[5])
		ft_putstr(_END);
}
