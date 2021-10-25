/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bite_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:34:55 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 20:33:34 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		set_reg_pos(t_vm *vm)
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

static int		do_bite(t_vm *vm, t_process *p, int v1, int v2)
{
	int		reg_pos;
	int		pc;
	int		reg;

	pc = p->program_counter;
	reg_pos = pc + 2 + set_reg_pos(vm);
	reg = vm->arena[(reg_pos) % MEM_SIZE];
	if (check_reg(reg) == TRUE)
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

static void		modify_reg_pos(t_vm *vm, t_process *p)
{
	int		value1;
	int		value2;

	value1 = get_value1(vm, p);
	value2 = get_value2(vm, p);
	vm->reg_pos = do_bite(vm, p, value1, value2);
	option_two(vm, p, value1, value2);
	vm->reg_pos++;
}

static int		check_valid_reg2(t_vm *vm, t_process *p)
{
	int		valid;
	int		pc_bis;

	valid = 1;
	pc_bis = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	if (ft_strequ(vm->ocp[0], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[0], _DIR))
		pc_bis += 4;
	else if (ft_strequ(vm->ocp[0], _IND))
		pc_bis += 2;
	if (ft_strequ(vm->ocp[1], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	if (ft_strequ(vm->ocp[1], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[1], _DIR))
		pc_bis += 4;
	else if (ft_strequ(vm->ocp[1], _IND))
		pc_bis += 2;
	if (ft_strequ(vm->ocp[2], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	return (valid);
}

int				bite_op(t_vm *vm, t_process *p)
{
	int		pc;

	vm->reg_pos = 0;
	pc = p->program_counter;
	if (vm->arena[(p->program_counter) % MEM_SIZE] == AND)
		return (and_op(vm, p));
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if (vm->option_v[5] == TRUE)
		ft_putstr(_GREEN);
	if ((!ft_strequ(vm->ocp[0], _REG) && !ft_strequ(vm->ocp[0], _IND) &&
			!ft_strequ(vm->ocp[0], _DIR)) || (!ft_strequ(vm->ocp[1], _REG) &&
			!ft_strequ(vm->ocp[1], _IND) && !ft_strequ(vm->ocp[1], _DIR)) ||
				!ft_strequ(vm->ocp[2], _REG))
	{
		pc += find_special_pc(vm);
		option_v_four(vm, pc, p);
		return (pc);
	}
	if (check_valid_reg2(vm, p))
		modify_reg_pos(vm, p);
	vm->reg_pos = p->program_counter + set_reg_pos(vm) + 3;
	option_v_four(vm, vm->reg_pos, p);
	if (vm->option_v[5] == TRUE)
		ft_putstr(_END);
	return (vm->reg_pos);
}
