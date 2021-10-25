/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 16:55:36 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 17:54:29 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		fill_colors(t_vm *vm, const int pc, const int address,
		t_process *process)
{
	vm->arena_owner[(pc + address) % MEM_SIZE] = process->color;
	vm->arena_moves[(pc + address) % MEM_SIZE] = process->color;
	vm->arena_owner[(pc + address + 1) % MEM_SIZE] = process->color;
	vm->arena_moves[(pc + address + 1) % MEM_SIZE] = process->color;
	vm->arena_owner[(pc + address + 2) % MEM_SIZE] = process->color;
	vm->arena_moves[(pc + address + 2) % MEM_SIZE] = process->color;
	vm->arena_owner[(pc + address + 3) % MEM_SIZE] = process->color;
	vm->arena_moves[(pc + address + 3) % MEM_SIZE] = process->color;
}

static int		execute_st_utils(t_vm *vm, t_process *process, int pc)
{
	int		*tab;
	int		address;

	tab = fill_tab_sti(process->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1]);
	address = (short)(vm->arena[(pc + 4) % MEM_SIZE]
			+ vm->arena[(pc + 3) % MEM_SIZE] * 16 * 16);
	if (vm->option_v[2])
		ft_printf("P %4d | st r%d %d\n", process->number,
				vm->arena[(process->program_counter + 2) % MEM_SIZE], address);
	address %= IDX_MOD;
	if ((address + pc) < 0)
		address = MEM_SIZE - (-address % IDX_MOD);
	vm->arena[(pc + address) % MEM_SIZE] = tab[0];
	vm->arena[(pc + address + 1) % MEM_SIZE] = tab[1];
	vm->arena[(pc + address + 2) % MEM_SIZE] = tab[2];
	vm->arena[(pc + address + 3) % MEM_SIZE] = tab[3];
	fill_colors(vm, pc, address, process);
	pc = pc + 5;
	free(tab);
	return (pc);
}

static int		execute_st(t_vm *vm, int pc, t_process *process)
{
	int		address;

	if (ft_strequ(vm->ocp[0], _REG) && ft_strequ(vm->ocp[1], _REG))
	{
		process->registers[vm->arena[(pc + 3) % MEM_SIZE] - 1] =
			process->registers[vm->arena[(pc + 2) % MEM_SIZE] - 1];
		address = vm->arena[(pc + 3) % MEM_SIZE];
		pc = pc + 4;
		if (vm->option_v[2])
			ft_printf("P %4d | st r%d %d\n", process->number,
					vm->arena[(process->program_counter + 2) % MEM_SIZE],
					address);
	}
	else if (ft_strequ(vm->ocp[0], _REG) && ft_strequ(vm->ocp[1], _IND))
	{
		pc = execute_st_utils(vm, process, pc);
	}
	option_v_four(vm, pc, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc);
}

static int		st_check_reg(t_vm *vm, int pc, t_process *process)
{
	int		valid;

	valid = 1;
	if (ft_strequ(vm->ocp[0], _REG)
			&& !check_reg(vm->arena[(pc + 2) % MEM_SIZE]))
		valid = 0;
	if (ft_strequ(vm->ocp[1], _REG)
			&& !check_reg(vm->arena[(pc + 3) % MEM_SIZE]))
		valid = 0;
	if (!valid)
	{
		if (ft_strequ(vm->ocp[0], _REG) && ft_strequ(vm->ocp[1], _REG))
		{
			pc += 4;
			option_v_four(vm, pc, process);
		}
		else if (ft_strequ(vm->ocp[0], _REG) && ft_strequ(vm->ocp[1], _IND))
		{
			pc += 5;
			option_v_four(vm, pc, process);
		}
		return (pc);
	}
	return (execute_st(vm, pc, process));
}

int				launch_st(t_vm *vm, t_process *process)
{
	int				pc;

	if (vm->option_v[5])
		ft_putstr(_CYAN);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if (!ft_strequ(vm->ocp[0], _REG) || !(ft_strequ(vm->ocp[1], _REG)
				|| ft_strequ(vm->ocp[1], _IND)))
	{
		pc += find_special_pc_terce(vm);
		option_v_four(vm, pc, process);
		return (pc);
	}
	return (st_check_reg(vm, pc, process));
}
