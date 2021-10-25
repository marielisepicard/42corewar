/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <manki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:43:50 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 18:26:04 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		op_sub(int *r1, int *r2, int *r3, char *carry)
{
	*r3 = *r1 - *r2;
	*carry = (*r3 == 0) ? 1 : 0;
}

static int		find_special_pc_sub(t_vm *vm)
{
	int		res;

	res = 0;
	if (ft_strequ(vm->ocp[0], _REG))
		res += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		res += 4;
	if (ft_strequ(vm->ocp[1], _REG))
		res += 1;
	else if (ft_strequ(vm->ocp[1], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		res += 4;
	if (ft_strequ(vm->ocp[2], _REG))
		res += 1;
	else if (ft_strequ(vm->ocp[2], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[2], _DIR))
		res += 4;
	res += 2;
	return (res);
}

static int		check_reg_sub(t_vm *vm, t_process *process, int pc)
{
	if (check_reg(vm->arena[(pc + 2) % MEM_SIZE]) &&
			check_reg(vm->arena[(pc + 3) % MEM_SIZE]) &&
			check_reg(vm->arena[(pc + 4) % MEM_SIZE]))
	{
		op_sub(&process->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1],
				&process->registers[vm->arena[(pc + 3) % MEM_SIZE] - 1],
				&process->registers[vm->arena[(pc + 4) % MEM_SIZE] - 1],
				&process->carry);
		if (vm->option_v[2])
			ft_printf("P %4d | sub r%d r%d r%d\n", process->number,
					vm->arena[(pc + 2) % MEM_SIZE],
					vm->arena[(pc + 3) % MEM_SIZE],
					vm->arena[(pc + 4) % MEM_SIZE]);
	}
	pc += 5;
	option_v_four(vm, pc, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc);
}

int				launch_sub(t_vm *vm, t_process *process)
{
	int		pc;

	if (vm->option_v[5])
		ft_putstr(_GREY);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if (!ft_strequ(vm->ocp[0], _REG) || !ft_strequ(vm->ocp[1], _REG) ||
			!ft_strequ(vm->ocp[2], _REG))
	{
		pc += find_special_pc_sub(vm);
		option_v_four(vm, pc, process);
		return (pc);
	}
	return (check_reg_sub(vm, process, pc));
}
