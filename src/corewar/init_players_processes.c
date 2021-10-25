/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <manki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:28:43 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 21:59:57 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	add_process(t_vm *vm, t_process *process)
{
	if (vm->process_list != NULL)
	{
		process->number = vm->process_list->number + 1;
		process->next = vm->process_list;
		vm->process_list = process;
	}
	else
	{
		process->number = 1;
		vm->process_list = process;
	}
}

static void	init_player_processes(t_vm *vm, t_player *curr_player, int pc)
{
	t_process	*process;
	size_t		size;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		exit_error(ERROR_MALLOC);
	process->name = curr_player->name;
	process->number = curr_player->number;
	if (process->number < 0)
		process->number *= -1;
	vm->last_process_number = process->number;
	process->color = curr_player->color;
	process->program_counter = pc;
	size = REG_NUMBER * sizeof(int);
	ft_bzero(process->registers, size);
	process->registers[0] = curr_player->number;
	process->carry = FALSE;
	process->running = -1;
	process->over = FALSE;
	process->live_calls = 0;
	process->alive = TRUE;
	process->is_fork = FALSE;
	process->cycles_to_wait = 0;
	process->since_last_live = -1;
	process->next = NULL;
	add_process(vm, process);
}

void		init_players_processes(t_vm *vm)
{
	int			i;
	size_t		position;

	i = 0;
	position = 0;
	while (i < vm->count_players)
	{
		init_player_processes(vm, &vm->players[i], position);
		position = position + (MEM_SIZE / vm->count_players);
		i++;
	}
}
