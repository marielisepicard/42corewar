/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <manki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 19:13:00 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 22:15:00 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	announce_winner(t_vm *vm, int keep_going)
{
	int		key;

	if (vm->last_alive_number < 0)
		vm->last_alive_number = -(vm->last_alive_number);
	if (vm->option_ncurse == FALSE)
	{
		if (vm->dump <= 0 || !keep_going)
			ft_printf("Contestant %d, \"%s\", has won !\n",
					vm->last_alive_number, vm->last_alive_name);
	}
	else
	{
		werase(vm->notif);
		if (vm->last_alive_name == NULL)
			wprintw(vm->notif, "There is no winner this time !\n");
		else
			wprintw(vm->notif, "The winner is Champion %d (%s) !\n",
					vm->last_alive_number, vm->last_alive_name);
		wnoutrefresh(vm->notif);
		doupdate();
		while ((key = getch()) != 'q')
			;
		del_ncurse(vm);
	}
}

static void	start_visu(t_vm *vm)
{
	if (vm->option_ncurse == TRUE)
	{
		reload_windows(vm, 1);
		reload_windows(vm, 2);
		reload_windows(vm, 3);
	}
}

static int	update_keep_going(t_vm *vm, int keep_going)
{
	if (vm->dump > 0)
	{
		if (vm->cycles < vm->dump)
			vm->cycles++;
	}
	else
		vm->cycles++;
	if (!vm->process_list)
		keep_going = 0;
	return (keep_going);
}

static void	cursors_killer(t_vm *vm)
{
	load_operations(vm, vm->cycles);
	if (vm->delta_ctd_copy < 1)
		kill_all_cursors(vm);
	else if (vm->cycles == vm->cycle_to_die || vm->cycle_to_die <= 1)
	{
		kill_dead_cursors(vm);
		update_ctd(vm);
		restore_live_calls(vm->process_list);
	}
}

void		launch_fight(t_vm *vm)
{
	int		keep_going;

	if (vm->dump == 0)
		vm->dump = 1;
	keep_going = 1;
	start_visu(vm);
	while (vm->process_list != NULL)
	{
		cursors_killer(vm);
		(vm->option_ncurse == TRUE) ? get_key() : 0;
		(vm->option_ncurse == TRUE) ? reload_windows(vm, 1) : 0;
		(vm->option_ncurse == TRUE) ? reload_windows(vm, 2) : 0;
		if (vm->cycles == vm->dump)
		{
			if (vm->process_list)
			{
				dump_arena(vm);
				break ;
			}
			else
				keep_going = 0;
		}
		keep_going = update_keep_going(vm, keep_going);
	}
	announce_winner(vm, keep_going);
}
