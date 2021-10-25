/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bite_op_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:54:30 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/12 13:59:58 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_value1(t_vm *vm, t_process *p)
{
	int		value1;
	int		pc;

	pc = p->program_counter;
	if (ft_strequ(vm->ocp[0], _REG)
			&& check_reg(vm->arena[(pc + 2) % MEM_SIZE]))
		value1 = p->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1];
	else if (ft_strequ(vm->ocp[0], _DIR))
		value1 = convert_dir(vm, pc + 2);
	else if (ft_strequ(vm->ocp[0], _IND))
		value1 = convert_ind(vm, pc + 2, pc);
	else
		value1 = 0;
	return (value1);
}

int		get_value2(t_vm *vm, t_process *p)
{
	int				pc;

	pc = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG))
		pc += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		pc += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		pc += 4;
	if (ft_strequ(vm->ocp[1], _REG) && check_reg(vm->arena[pc % MEM_SIZE]))
		return (p->registers[vm->arena[pc % MEM_SIZE] - 1]);
	else if (ft_strequ(vm->ocp[1], _DIR))
		return (convert_dir(vm, pc));
	else if (ft_strequ(vm->ocp[1], _IND))
		return (convert_ind(vm, pc, p->program_counter));
	return (FAILURE);
}
