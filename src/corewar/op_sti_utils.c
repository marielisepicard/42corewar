/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:24:15 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 17:27:31 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		set_pc_position(t_vm *vm, t_process *process, int pos)
{
	int		pc;
	int		i;

	pc = process->program_counter + 2;
	i = -1;
	while (++i < pos)
	{
		if (ft_strequ(vm->ocp[i], _REG))
			pc += 1;
		else if (ft_strequ(vm->ocp[i], _DIR) || ft_strequ(vm->ocp[i], _IND))
			pc += 2;
	}
	return (pc);
}

void	set_colors(t_vm *vm, t_process *process, int res)
{
	int		var;

	var = process->program_counter + res;
	vm->arena_owner[var % MEM_SIZE] = process->color;
	vm->arena_moves[var % MEM_SIZE] = process->color;
	vm->arena_owner[(var + 1) % MEM_SIZE] = process->color;
	vm->arena_moves[(var + 1) % MEM_SIZE] = process->color;
	vm->arena_owner[(var + 2) % MEM_SIZE] = process->color;
	vm->arena_moves[(var + 2) % MEM_SIZE] = process->color;
	vm->arena_owner[(var + 3) % MEM_SIZE] = process->color;
	vm->arena_moves[(var + 3) % MEM_SIZE] = process->color;
}

int		set_param2_utils(t_vm *vm, int pc, int param2)
{
	unsigned int	add;
	unsigned int	c;

	add = 0;
	c = 16;
	add = (vm->arena[(pc + 4) % MEM_SIZE]
				+ vm->arena[(pc + 3) % MEM_SIZE] * 16 * 16);
	param2 += vm->arena[(pc + add + 3) % MEM_SIZE];
	param2 += vm->arena[(pc + add + 2) % MEM_SIZE] * c * c;
	param2 += vm->arena[(pc + add + 1) % MEM_SIZE] * c * c * c * c;
	param2 += vm->arena[(pc + add) % MEM_SIZE] * c * c * c * c * c * c;
	return (param2);
}

int		set_param2(t_vm *vm, t_process *process)
{
	int				param2;
	int				pc;

	param2 = 0;
	pc = process->program_counter + 3;
	if (ft_strequ(vm->ocp[1], _REG) &&
			check_reg(vm->arena[(pc) % MEM_SIZE]))
		param2 = process->registers[vm->arena[(pc) % MEM_SIZE] - 1];
	else if (ft_strequ(vm->ocp[1], _DIR))
	{
		param2 = vm->arena[(pc + 1) % MEM_SIZE];
		param2 += vm->arena[(pc) % MEM_SIZE] * 16 * 16;
		param2 = (short)param2;
	}
	else if (ft_strequ(vm->ocp[1], _IND))
	{
		pc -= 3;
		param2 = set_param2_utils(vm, pc, param2);
	}
	return (param2);
}

int		set_param3(t_vm *vm, t_process *process)
{
	int		param3;
	int		pc;

	param3 = 0;
	pc = set_pc_position(vm, process, 2);
	if (ft_strequ(vm->ocp[2], _DIR))
	{
		param3 = vm->arena[(pc + 1) % MEM_SIZE];
		param3 += vm->arena[(pc) % MEM_SIZE] * 16 * 16;
		param3 = (short)param3;
	}
	else if (ft_strequ(vm->ocp[2], _REG) &&
			check_reg(vm->arena[(pc) % MEM_SIZE]))
		param3 = process->registers[vm->arena[(pc) % MEM_SIZE] - 1];
	return (param3);
}
