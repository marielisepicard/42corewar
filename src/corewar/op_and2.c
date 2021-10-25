/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:16:00 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 20:32:49 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_and_value1(t_vm *vm, t_process *p)
{
	int		value1;
	int		pc;

	pc = p->program_counter;
	if (ft_strequ(vm->ocp[0], _REG))
		value1 = p->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1];
	else if (ft_strequ(vm->ocp[0], _DIR))
		value1 = convert_dir(vm, pc + 2);
	else if (ft_strequ(vm->ocp[0], _IND))
		value1 = convert_ind(vm, pc + 2, pc);
	else
		value1 = 0;
	return (value1);
}

static int	get_and_value2(t_vm *vm, t_process *p)
{
	int		pc;

	pc = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG))
		pc += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		pc += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		pc += 4;
	if (ft_strequ(vm->ocp[1], _REG))
		return (p->registers[vm->arena[pc % MEM_SIZE] - 1]);
	else if (ft_strequ(vm->ocp[1], _DIR))
		return (convert_dir(vm, pc));
	else if (ft_strequ(vm->ocp[1], _IND))
		return (convert_ind(vm, pc, p->program_counter));
	return (FAILURE);
}

int			and_op2(t_vm *vm, t_process *p, int pc)
{
	int		value1;
	int		value2;
	int		pc_bis;

	pc_bis = set_pc_bis(vm, p);
	value1 = get_and_value1(vm, p);
	value2 = get_and_value2(vm, p);
	if (!vm->valid)
	{
		pc = p->program_counter;
		vm->reg_pos = pc + 4 + set_reg_pos_and(vm);
		option_v_four(vm, vm->reg_pos, p);
		vm->reg_pos++;
		return (vm->reg_pos);
	}
	vm->reg_pos = do_and(vm, p, value1, value2);
	option_two(vm, p, value1, value2);
	vm->reg_pos++;
	option_v_four(vm, vm->reg_pos, p);
	if (vm->option_v[5] == TRUE)
		ft_putstr(_END);
	return (vm->reg_pos);
}
