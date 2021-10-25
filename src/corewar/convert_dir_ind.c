/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dir_ind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 12:40:30 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 16:56:59 by manki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	convert_dir(t_vm *vm, int index)
{
	unsigned int	convert_dir;
	unsigned int	c;

	c = 16;
	if (index < 0)
		index = MEM_SIZE + (index % MEM_SIZE);
	convert_dir = vm->arena[(index + 3) % MEM_SIZE];
	convert_dir += vm->arena[(index + 2) % MEM_SIZE] * c * c;
	convert_dir += vm->arena[(index + 1) % MEM_SIZE] * c * c * c * c;
	convert_dir += vm->arena[index % MEM_SIZE] * c * c * c * c * c * c;
	return (convert_dir);
}

unsigned int	convert_ind(t_vm *vm, int index, int pc)
{
	short			convert_ind;
	unsigned int	res;

	convert_ind = vm->arena[(index + 1) % MEM_SIZE];
	convert_ind += vm->arena[index % MEM_SIZE] * 16 * 16;
	pc %= MEM_SIZE;
	if (vm->arena[pc] != LLD && vm->arena[pc] != LLDI && vm->arena[pc] != LFORK)
		res = convert_dir(vm, (pc + (convert_ind % IDX_MOD)) % MEM_SIZE);
	else
		res = convert_dir(vm, pc + convert_ind);
	return (res);
}

int				convert_4bytes(t_vm *vm, t_process *p, int index)
{
	int				res;
	unsigned int	c;
	int				pc;

	c = 16;
	pc = p->program_counter;
	res = vm->arena[(pc + index) % MEM_SIZE] * c * c * c * c * c * c;
	res += vm->arena[(pc + index + 1) % MEM_SIZE] * c * c * c * c;
	res += vm->arena[(pc + index + 2) % MEM_SIZE] * c * c;
	res += vm->arena[(pc + index + 3) % MEM_SIZE];
	return (res);
}
