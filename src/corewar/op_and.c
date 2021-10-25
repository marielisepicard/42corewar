/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:16:00 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 20:35:08 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	set_reg_pos_and(t_vm *vm)
{
	int	reg_pos;

	reg_pos = 0;
	if (ft_strequ(vm->ocp[0], _REG))
		reg_pos += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		reg_pos += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		reg_pos += 4;
	if (ft_strequ(vm->ocp[1], _REG))
		reg_pos += 1;
	else if (ft_strequ(vm->ocp[1], _IND))
		reg_pos += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		reg_pos += 4;
	return (reg_pos);
}

int	do_and(t_vm *vm, t_process *p, int v1, int v2)
{
	int		reg_pos;
	int		pc;
	int		reg;

	pc = p->program_counter;
	reg_pos = pc + 2 + set_reg_pos_and(vm);
	reg = vm->arena[(reg_pos) % MEM_SIZE];
	if (check_reg(reg))
	{
		if (vm->arena[(pc) % MEM_SIZE] == AND)
			p->registers[reg - 1] = v1 & v2;
		else if (vm->arena[(pc) % MEM_SIZE] == OR)
			p->registers[reg - 1] = v1 | v2;
		else if (vm->arena[(pc) % MEM_SIZE] == XOR)
			p->registers[reg - 1] = v1 ^ v2;
		p->carry = (p->registers[reg - 1] == 0) ? 1 : 0;
	}
	else
		p->carry = 0;
	return (reg_pos);
}

int	set_pc_bis(t_vm *vm, t_process *p)
{
	int		pc_bis;

	pc_bis = p->program_counter + 2;
	vm->valid = 1;
	if (ft_strequ(vm->ocp[0], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		vm->valid = 0;
	if (ft_strequ(vm->ocp[0], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		pc_bis += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		pc_bis += 4;
	if (ft_strequ(vm->ocp[1], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		vm->valid = 0;
	if (ft_strequ(vm->ocp[1], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[1], _IND))
		pc_bis += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		pc_bis += 4;
	if (ft_strequ(vm->ocp[2], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		vm->valid = 0;
	return (pc_bis);
}

int	and_op(t_vm *vm, t_process *p)
{
	int		pc;

	vm->reg_pos = 0;
	vm->valid = 0;
	pc = p->program_counter;
	if (vm->option_v[5] == TRUE)
		ft_putstr(_GREEN);
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if ((!ft_strequ(vm->ocp[0], _REG) && !ft_strequ(vm->ocp[0], _IND)
				&& !ft_strequ(vm->ocp[0], _DIR))
			|| (!ft_strequ(vm->ocp[1], _REG)
				&& !ft_strequ(vm->ocp[1], _IND) && !ft_strequ(vm->ocp[1], _DIR))
			|| !ft_strequ(vm->ocp[2], _REG))
	{
		pc += find_special_pc(vm);
		option_v_four(vm, pc, p);
		return (pc);
	}
	return (and_op2(vm, p, pc));
}
