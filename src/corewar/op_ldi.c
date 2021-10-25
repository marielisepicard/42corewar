/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:28:35 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 18:58:31 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		getpar1(t_vm *vm, t_process *p)
{
	int				par1;
	int				tmp;
	int				pc;

	pc = p->program_counter;
	par1 = 0;
	tmp = 0;
	if (ft_strequ(vm->ocp[0], _IND))
	{
		tmp = vm->arena[(pc + 2) % MEM_SIZE] * 16 * 16;
		tmp += vm->arena[(pc + 3) % MEM_SIZE];
		par1 = convert_4bytes(vm, p, tmp % IDX_MOD);
	}
	else if (ft_strequ(vm->ocp[0], _DIR))
	{
		par1 = (vm->arena[(pc + 2) % MEM_SIZE] * 16 * 16);
		par1 += vm->arena[(pc + 3) % MEM_SIZE];
		par1 = (short)par1;
	}
	else if (ft_strequ(vm->ocp[0], _REG) &&
			check_reg(vm->arena[(pc + 2) % MEM_SIZE]))
		par1 = p->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1];
	return (par1);
}

static int		getpar2_ldi(t_vm *vm, t_process *p)
{
	int				par2;
	int				pc;

	par2 = 0;
	pc = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG))
		pc += 1;
	else if (ft_strequ(vm->ocp[0], _IND) || ft_strequ(vm->ocp[0], _DIR))
		pc += 2;
	if (ft_strequ(vm->ocp[1], _DIR))
	{
		par2 = vm->arena[pc % MEM_SIZE] * 16 * 16;
		par2 += vm->arena[(pc + 1) % MEM_SIZE];
		par2 = (short)par2;
	}
	else if (ft_strequ(vm->ocp[1], _REG) &&
			check_reg(vm->arena[pc % MEM_SIZE]))
		par2 = p->registers[vm->arena[pc % MEM_SIZE] - 1];
	return (par2);
}

int				check_valid_reg(t_vm *vm, t_process *p)
{
	int		valid;
	int		pc_bis;

	valid = 1;
	pc_bis = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	if (ft_strequ(vm->ocp[0], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[0], _DIR) || ft_strequ(vm->ocp[0], _IND))
		pc_bis += 2;
	if (ft_strequ(vm->ocp[1], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	if (ft_strequ(vm->ocp[1], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[1], _DIR))
		pc_bis += 2;
	if (ft_strequ(vm->ocp[2], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	return (valid);
}

static void		do_ldi(t_vm *vm, t_process *p)
{
	int		first;
	int		second;
	int		sum;
	int		pc;
	int		reg;

	pc = p->program_counter;
	first = getpar1(vm, p);
	second = getpar2_ldi(vm, p);
	sum = first + second;
	reg = vm->arena[get_new_position(vm, p->program_counter, 2) % MEM_SIZE];
	p->registers[reg - 1] = convert_4bytes(vm, p, sum % IDX_MOD);
	if (vm->option_v[2])
	{
		ft_printf("P %4d | ldi %d %d r%d\n", p->number,
				first, second, reg);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				first, second, sum, pc + (sum % IDX_MOD));
	}
}

int				launch_ldi(t_vm *vm, t_process *process)
{
	int				pc;
	int				reg;

	if (vm->option_v[5])
		ft_putstr(_PURPLE);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if ((!ft_strequ(vm->ocp[0], _REG) && !ft_strequ(vm->ocp[0], _DIR) &&
			!ft_strequ(vm->ocp[0], _IND)) || (!ft_strequ(vm->ocp[1], _REG) &&
			!ft_strequ(vm->ocp[1], _DIR)) || !ft_strequ(vm->ocp[2], _REG))
		return (wrong_params(vm, process, pc + find_special_pc_bis(vm)));
	if (check_valid_reg(vm, process))
		do_ldi(vm, process);
	reg = get_new_position(vm, pc, 3);
	option_v_four(vm, reg, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (reg);
}
