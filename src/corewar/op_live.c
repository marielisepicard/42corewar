/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 14:42:49 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 20:26:50 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		find_name(t_vm *vm, int player_number)
{
	int		i;

	i = 0;
	while (i < vm->count_players)
	{
		if (vm->players[i].number == player_number)
			return (i);
		i++;
	}
	return (-1);
}

static void		option_ncurse(t_vm *vm, int index)
{
	wprintw(vm->notif, "Champion ");
	wattron(vm->notif, COLOR_PAIR(vm->players[index].color) | A_BOLD);
	if (vm->last_alive_number < 0)
		wprintw(vm->notif, "%d", -vm->last_alive_number);
	else
		wprintw(vm->notif, "%d", vm->last_alive_number);
	wattroff(vm->notif, COLOR_PAIR(vm->players[index].color) | A_BOLD);
	wprintw(vm->notif, " (");
	wattron(vm->notif, COLOR_PAIR(vm->players[index].color) | A_BOLD);
	wprintw(vm->notif, "%s", vm->last_alive_name);
	wattroff(vm->notif, COLOR_PAIR(vm->players[index].color) | A_BOLD);
	wprintw(vm->notif, ")");
	wprintw(vm->notif, " is alive\n");
	reload_windows(vm, 3);
}

static void		live_success(t_vm *vm, int index, int player_number)
{
	vm->last_alive_name = vm->players[index].name;
	vm->last_alive_number = player_number;
	vm->players[index].lives++;
	if (vm->option_v[6])
		ft_printf("Player %d (%s) is said to be alive\n",
				-player_number, vm->last_alive_name);
	if (vm->option_ncurse == TRUE)
		option_ncurse(vm, index);
}

int				op_live(t_vm *vm, t_process *process)
{
	int			player_number;
	int			index;

	if (vm->option_v[5] == TRUE)
		ft_putstr(_GREEN);
	player_number = convert_dir(vm, process->program_counter + 1);
	if (process && process->alive)
	{
		process->live_calls++;
		vm->live_calls++;
		index = find_name(vm, player_number);
		if (index != -1)
			live_success(vm, index, player_number);
		if (vm->option_v[2] == TRUE)
			ft_printf("P %4d | live %d\n", process->number, player_number);
		process->since_last_live = 0;
	}
	option_v_four(vm, process->program_counter + 5, process);
	if (vm->option_v[5] == TRUE)
		ft_putstr(_END);
	return (process->program_counter + 5);
}
