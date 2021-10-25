/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 14:43:22 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 19:12:52 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		find_special_pc_aff(t_vm *vm)
{
	int		res;

	res = 0;
	if (ft_strequ(vm->ocp[0], _REG))
		res += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		res += 4;
	res += 2;
	return (res);
}

static void		option_v_aff(t_vm *vm, t_process *process, int pc, int reg)
{
	if (vm->option_v[6])
		if (check_reg(reg))
			ft_printf("Aff: %c\n", process->registers[reg]);
	if (vm->option_v[4])
	{
		ft_printf("ADV 3 (0x%.4x -> 0x%.4x) %.2x %.2x %.2x \n",
				pc - 3, pc, vm->arena[(pc - 3) % MEM_SIZE],
				vm->arena[(pc - 2) % MEM_SIZE], vm->arena[(pc - 1) % MEM_SIZE]);
	}
	if (vm->option_v[5])
		ft_putstr(_END);
}

int				op_aff(t_vm *vm, t_process *process)
{
	int		reg;
	int		pc;

	if (vm->option_v[5])
		ft_putstr(_RED);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[pc + 1]);
	pc += find_special_pc_aff(vm);
	if (!ft_strequ(vm->ocp[0], _REG))
	{
		option_v_four(vm, pc, process);
		return (pc);
	}
	reg = vm->arena[(process->program_counter + 2) % MEM_SIZE];
	option_v_aff(vm, process, pc, reg);
	return (pc);
}
