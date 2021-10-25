/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:28:51 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/13 22:09:53 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	initialize_tabs(t_vm *vm)
{
	size_t size;

	size = MAX_PLAYERS * sizeof(t_player);
	ft_bzero(vm->players, size);
	size = MEM_SIZE * sizeof(unsigned char);
	ft_bzero(vm->arena, size);
	size = OPTION_V_SIZE * sizeof(int8_t);
	ft_bzero(vm->option_v, size);
	size = MEM_SIZE * sizeof(int);
	ft_bzero(vm->arena_moves, size);
	ft_bzero(vm->arena_owner, size);
	size = 5 * sizeof(char);
	ft_bzero(vm->buf, 5 * sizeof(char));
	size = MAX_PLAYERS * sizeof(int);
	ft_bzero(vm->code_sizes, size);
}

void		initialize_vm(t_vm *vm, char **av)
{
	vm->option_ncurse = FALSE;
	vm->count_players = 0;
	vm->dump = -1;
	vm->champion_files = av;
	vm->process_list = NULL;
	vm->last_alive_number = 0;
	vm->last_alive_name = NULL;
	vm->live_calls = 0;
	vm->cycles = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->neg_ctd = 0;
	vm->delta_ctd = 1536;
	vm->delta_ctd_copy = 1536;
	vm->check_number = 0;
	vm->cpt_notifs = 0;
	vm->usleep = SLEEP_TIME;
	vm->reg_pos = 0;
	vm->reg = 0;
	vm->valid = 0;
	vm->last_process_number = 0;
	initialize_tabs(vm);
	set_tab_pow(vm);
}
