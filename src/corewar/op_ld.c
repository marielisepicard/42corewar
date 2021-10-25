/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <manki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:37:31 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 16:34:30 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_ld(int value, int *r, char *carry)
{
	*r = value;
	*carry = (*r == 0) ? 1 : 0;
}

static int		set_len(t_vm *vm)
{
	int		len;

	len = 0;
	if (ft_strequ(vm->ocp[0], _DIR))
		len = 6;
	else if (ft_strequ(vm->ocp[0], _IND))
		len = 4;
	return (len);
}

static int		get_value(t_vm *vm, int pc)
{
	unsigned int	c;
	int				value;

	value = 0;
	c = 16;
	if (ft_strequ(vm->ocp[0], _DIR) && ft_strequ(vm->ocp[1], _REG))
	{
		value = vm->arena[(pc + 5) % MEM_SIZE];
		value += vm->arena[(pc + 4) % MEM_SIZE] * 16 * 16;
		value += vm->arena[(pc + 3) % MEM_SIZE] * 16 * 16 * 16 * 16;
		value += vm->arena[(pc + 2) % MEM_SIZE] * c * c * c * c * c * c;
	}
	else if (ft_strequ(vm->ocp[0], _IND) && ft_strequ(vm->ocp[1], _REG))
		value = convert_ind(vm, pc + 2, pc);
	return (value);
}

int				wrong_params(t_vm *vm, t_process *p, int pc)
{
	option_v_four(vm, pc, p);
	return (pc);
}

int				launch_ld(t_vm *vm, t_process *p)
{
	int				pc;
	int				l;
	int				value;

	if (vm->option_v[5])
		ft_putstr(_PURPLE);
	pc = p->program_counter;
	ft_itobin(vm, vm->arena[(pc + 1) % MEM_SIZE]);
	l = set_len(vm);
	if (!(ft_strequ(vm->ocp[0], _DIR) || ft_strequ(vm->ocp[0], _IND)) ||
		!ft_strequ(vm->ocp[1], _REG))
		return (wrong_params(vm, p, pc + find_special_pc_terce(vm)));
	else if (!check_reg(vm->arena[(pc + l) % MEM_SIZE]))
		return (wrong_params(vm, p, pc + l + 1));
	value = get_value(vm, pc);
	op_ld(value, &p->registers[vm->arena[(pc + l) % MEM_SIZE] - 1], &p->carry);
	if (vm->option_v[2])
		ft_printf("P %4d | ld %d r%d\n", p->number, value,
				vm->arena[(pc + l) % MEM_SIZE]);
	option_v_four(vm, pc + l + 1, p);
	if (vm->option_v[5])
		ft_putstr(_END);
	return (pc + l + 1);
}
