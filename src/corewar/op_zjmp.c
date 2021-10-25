/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 14:43:55 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 20:20:27 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			op_zjmp(t_vm *vm, t_process *process)
{
	short	value;
	int		pc;

	if (vm->option_v[5])
		ft_putstr(_GREEN);
	value = vm->arena[(process->program_counter + 2) % MEM_SIZE];
	value += vm->arena[(process->program_counter + 1) % MEM_SIZE] * 16 * 16;
	if (process->carry)
		pc = process->program_counter + (value % IDX_MOD);
	else
		pc = process->program_counter + 3;
	if (vm->option_v[2])
	{
		ft_printf("P %4d | zjmp %d", process->number, value);
		if (process->carry)
			ft_printf(" OK\n");
		else
			ft_printf(" FAILED\n");
	}
	if (!process->carry)
		option_v_four(vm, pc, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc);
}
