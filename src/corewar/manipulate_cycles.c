/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_cycles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:11:07 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 22:16:19 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_cycle_to_wait(int op)
{
	int		cycles;

	cycles = 0;
	if (op == LD || op == ST)
		cycles = 5;
	else if (op == LIVE || op == ADD || op == SUB || op == LLD)
		cycles = 10;
	else if (op == AND || op == OR || op == XOR)
		cycles = 6;
	else if (op == ZJMP)
		cycles = 20;
	else if (op == LDI || op == STI)
		cycles = 25;
	else if (op == FORK)
		cycles = 800;
	else if (op == LLDI)
		cycles = 50;
	else if (op == LFORK)
		cycles = 1000;
	else if (op == AFF)
		cycles = 2;
	return (cycles);
}

void		update_ctd_utils(t_vm *vm)
{
	vm->check_number = 0;
	vm->delta_ctd -= 50;
	vm->delta_ctd_copy = vm->delta_ctd;
	if (vm->option_v[1])
		ft_printf("Cycle to die is now %d\n", vm->delta_ctd_copy);
	if (vm->delta_ctd <= 0)
	{
		vm->neg_ctd = vm->delta_ctd;
		vm->delta_ctd = 1;
	}
}

void		update_ctd(t_vm *vm)
{
	if (vm->live_calls >= NBR_LIVE)
	{
		vm->delta_ctd -= 50;
		vm->delta_ctd_copy = vm->delta_ctd;
		if (vm->option_v[1])
			ft_printf("Cycle to die is now %d\n", vm->delta_ctd_copy);
		if (vm->delta_ctd < 0)
			vm->delta_ctd = 1;
		vm->cycle_to_die = vm->cycles + vm->delta_ctd;
		vm->check_number = 0;
	}
	else
	{
		vm->check_number++;
		if (vm->check_number == MAX_CHECKS)
			update_ctd_utils(vm);
		vm->cycle_to_die += vm->delta_ctd;
	}
	vm->live_calls = 0;
}
