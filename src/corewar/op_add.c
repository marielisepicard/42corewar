/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <manki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:12:58 by manki             #+#    #+#             */
/*   Updated: 2020/02/12 21:46:53 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	op_add(int *r1, int *r2, int *r3, char *carry)
{
	*r3 = *r1 + *r2;
	*carry = (*r3 == 0) ? 1 : 0;
}

static void	ex_add(t_vm *vm, t_process *process, int pc)
{
	op_add(&process->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1],
			&process->registers[vm->arena[(pc + 3) % MEM_SIZE] - 1],
			&process->registers[vm->arena[(pc + 4) % MEM_SIZE] - 1],
			&process->carry);
	if (vm->option_v[2])
		ft_printf("P %4d | add r%d r%d r%d\n", process->number,
				vm->arena[(pc + 2) % MEM_SIZE],
				vm->arena[(pc + 3) % MEM_SIZE],
				vm->arena[(pc + 4) % MEM_SIZE]);
}

int			launch_add(t_vm *vm, t_process *process)
{
	int		pc;

	pc = process->program_counter;
	if (vm->option_v[5])
		ft_putstr(_GREY);
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if (!ft_strequ(vm->ocp[0], _REG) || !ft_strequ(vm->ocp[1], _REG)
			|| !ft_strequ(vm->ocp[2], _REG))
	{
		pc += find_special_pc(vm);
		option_v_four(vm, pc, process);
		return (pc);
	}
	if (ft_strequ(vm->ocp[0], _REG) && ft_strequ(vm->ocp[1], _REG)
			&& ft_strequ(vm->ocp[2], _REG)
			&& check_reg(vm->arena[(pc + 2) % MEM_SIZE])
			&& check_reg(vm->arena[(pc + 3) % MEM_SIZE])
			&& check_reg(vm->arena[(pc + 4) % MEM_SIZE]))
		ex_add(vm, process, pc);
	pc += 5;
	option_v_four(vm, pc, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc);
}
