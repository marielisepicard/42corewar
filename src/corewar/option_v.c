/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:26:11 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 17:39:37 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	option_v_four(t_vm *vm, int pc, t_process *p)
{
	int		i;

	i = 0;
	if (vm->option_v[4] == TRUE && (pc - p->program_counter) > 0)
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x)", pc - p->program_counter,
				p->program_counter, pc);
		while (i < (pc - p->program_counter))
		{
			ft_printf(" %.2x", vm->arena[(p->program_counter + i) % MEM_SIZE]);
			i++;
		}
		ft_putendl(" ");
	}
}

void	option_two(t_vm *vm, t_process *p,
		const int value1, const int value2)
{
	if (vm->option_v[2] == TRUE && check_reg(vm->arena[vm->reg_pos]))
	{
		ft_printf("P %4d | ", p->number);
		if (vm->arena[(p->program_counter) % MEM_SIZE] == AND)
			ft_printf("and ");
		else if (vm->arena[(p->program_counter) % MEM_SIZE] == OR)
			ft_printf("or ");
		else
			ft_printf("xor ");
		ft_printf("%d %d r%d\n", value1, value2,
				vm->arena[(vm->reg_pos) % MEM_SIZE]);
	}
}
