/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:18:49 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 19:01:37 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_new_position(t_vm *vm, int pc, int pos)
{
	int		i;

	i = -1;
	pc += 2;
	while (++i < pos)
	{
		if (ft_strequ(vm->ocp[i], _REG))
			pc += 1;
		else if (ft_strequ(vm->ocp[i], _DIR) || ft_strequ(vm->ocp[i], _IND))
			pc += 2;
	}
	return (pc);
}

static int		get_par2(t_vm *vm, t_process *p)
{
	int		par2;
	int		tmp;
	int		pc;

	par2 = 0;
	tmp = 0;
	pc = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG))
		pc += 1;
	else if (ft_strequ(vm->ocp[0], _IND))
		pc += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		pc += 4;
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

static int		get_par1(t_vm *vm, t_process *p)
{
	int				par1;
	int				tmp;
	unsigned int	c;
	int				pc;

	par1 = 0;
	tmp = 0;
	c = 16;
	pc = p->program_counter;
	if (ft_strequ(vm->ocp[0], _IND))
	{
		tmp = vm->arena[(pc + 2) % MEM_SIZE] * c * c;
		tmp += vm->arena[(pc + 3) % MEM_SIZE];
		par1 = convert_4bytes(vm, p, tmp);
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

static void		do_lldi(t_vm *vm, t_process *p)
{
	int				first;
	int				second;
	int				reg;
	int				sum;
	int				pc;

	pc = p->program_counter;
	first = get_par1(vm, p);
	second = get_par2(vm, p);
	sum = first + second;
	reg = vm->arena[get_new_position(vm, p->program_counter, 2) % MEM_SIZE];
	p->registers[reg - 1] = convert_4bytes(vm, p, sum);
	p->carry = (p->registers[reg - 1] == 0) ? 1 : 0;
	if (vm->option_v[2])
	{
		ft_printf("P %4d | lldi %d %d r%d\n", p->number,
				first, second, reg);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
				first, second, sum, sum + pc);
	}
}

int				launch_lldi(t_vm *vm, t_process *process)
{
	int		pc;

	if (vm->option_v[5])
		ft_putstr(_PURPLE);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if ((!ft_strequ(vm->ocp[0], _REG) && !ft_strequ(vm->ocp[0], _DIR) &&
			!ft_strequ(vm->ocp[0], _IND)) || (!ft_strequ(vm->ocp[1], _REG) &&
			!ft_strequ(vm->ocp[1], _DIR)) || !ft_strequ(vm->ocp[2], _REG))
		return (wrong_params(vm, process, pc + find_special_pc_bis(vm)));
	if (check_valid_reg(vm, process))
		do_lldi(vm, process);
	pc = get_new_position(vm, process->program_counter, 3);
	option_v_four(vm, pc, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc);
}
