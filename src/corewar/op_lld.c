/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:50:04 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 17:51:05 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_value(t_vm *vm, int *pc)
{
	int		tmp;
	int		value;

	tmp = 0;
	value = 0;
	if (ft_strequ(vm->ocp[0], _DIR) && ft_strequ(vm->ocp[1], _REG) &&
			check_reg(vm->arena[(pc[0] + 6) % MEM_SIZE]))
	{
		value = convert_dir(vm, pc[0] + 2);
		pc[0] += 6;
	}
	else if (ft_strequ(vm->ocp[0], _IND) && ft_strequ(vm->ocp[1], _REG) &&
			check_reg(vm->arena[(pc[0] + 4) % MEM_SIZE]))
	{
		tmp = vm->arena[(pc[0] + 2) % MEM_SIZE] * 16 * 16;
		tmp += vm->arena[(pc[0] + 3) % MEM_SIZE];
		value = vm->arena[(pc[0] + tmp + 1) % MEM_SIZE];
		value += vm->arena[(pc[0] + tmp) % MEM_SIZE] * 16 * 16;
		value = (short)value;
		pc[0] += 4;
	}
	return (value);
}

int				launch_lld(t_vm *vm, t_process *process)
{
	int		value;
	int		pc;

	if (vm->option_v[5])
		ft_putstr(_PURPLE);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if (((!ft_strequ(vm->ocp[0], _DIR) && !ft_strequ(vm->ocp[0], _IND)) ||
				!ft_strequ(vm->ocp[1], _REG)))
		return (wrong_params(vm, process, pc + find_special_pc_terce(vm)));
	value = get_value(vm, &pc);
	if (check_reg(vm->arena[(pc) % MEM_SIZE]) == TRUE)
	{
		op_ld(value, &process->registers[vm->arena[(pc) % MEM_SIZE] - 1],
				&process->carry);
		if (vm->option_v[2])
			ft_printf("P %4d | lld %d r%d\n", process->number,
					value, vm->arena[(pc) % MEM_SIZE]);
	}
	option_v_four(vm, pc + 1, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc + 1);
}
