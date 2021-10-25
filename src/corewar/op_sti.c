/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:23:30 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 20:22:33 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	sti_option_two(int param2, int param3,
		t_process *process, t_vm *vm)
{
	if (vm->option_v[2])
	{
		ft_printf("P %4d | sti r%d %d ", process->number, vm->reg, param2);
		ft_printf("%d\n", param3);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				param2, param3, param2 + param3,
				process->program_counter + ((param2 + param3) % IDX_MOD));
	}
}

static void	sti_utils(t_vm *vm, t_process *process, int res)
{
	int		*tab;

	tab = fill_tab_sti(process->registers[vm->reg - 1]);
	vm->arena[(process->program_counter + res) % MEM_SIZE] = tab[0];
	vm->arena[(process->program_counter + res + 1) % MEM_SIZE] = tab[1];
	vm->arena[(process->program_counter + res + 2) % MEM_SIZE] = tab[2];
	vm->arena[(process->program_counter + res + 3) % MEM_SIZE] = tab[3];
	set_colors(vm, process, res);
	free(tab);
}

static int	check_valid_reg3(t_vm *vm, t_process *p)
{
	int		valid;
	int		pc_bis;

	valid = 1;
	pc_bis = p->program_counter + 2;
	if (ft_strequ(vm->ocp[0], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	if (ft_strequ(vm->ocp[0], _REG))
		pc_bis += 1;
	if (ft_strequ(vm->ocp[1], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	if (ft_strequ(vm->ocp[1], _REG))
		pc_bis += 1;
	else if (ft_strequ(vm->ocp[1], _DIR) || ft_strequ(vm->ocp[1], _IND))
		pc_bis += 2;
	if (ft_strequ(vm->ocp[2], _REG) && !check_reg(vm->arena[pc_bis % MEM_SIZE]))
		return (0);
	return (valid);
}

static int	do_sti(t_vm *vm, t_process *process)
{
	int				param2;
	int				param3;
	int				pc;
	int				res;

	param2 = set_param2(vm, process);
	param3 = set_param3(vm, process);
	res = (param2 + param3) % IDX_MOD;
	if (res < 0)
		res = MEM_SIZE + res;
	vm->reg = vm->arena[(process->program_counter + 2) % MEM_SIZE];
	pc = set_pc_position(vm, process, 2);
	pc = set_pc_position(vm, process, 3);
	sti_utils(vm, process, res);
	sti_option_two(param2, param3, process, vm);
	return (pc);
}

int			launch_sti(t_vm *vm, t_process *process)
{
	int				pc;

	if (vm->option_v[5])
		ft_putstr(_CYAN);
	pc = process->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	if (!ft_strequ(vm->ocp[0], _REG) || (!ft_strequ(vm->ocp[1], _REG) &&
				!ft_strequ(vm->ocp[1], _DIR) && !ft_strequ(vm->ocp[1], _IND)) ||
			(!ft_strequ(vm->ocp[2], _REG) && !ft_strequ(vm->ocp[2], _DIR)))
		return (wrong_params(vm, process, pc + find_special_pc_quarte(vm)));
	if (check_valid_reg3(vm, process))
		do_sti(vm, process);
	pc = set_pc_position(vm, process, 3);
	option_v_four(vm, pc, process);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc);
}
