/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 12:01:51 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 19:03:29 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_process	*get_color_process(t_vm *vm, int *color)
{
	t_process	*curr;

	curr = vm->process_list;
	while (curr)
	{
		if (curr->program_counter == *color)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static void			pc_colors(t_vm *vm, int *color, int on)
{
	t_process	*curr;

	curr = vm->process_list;
	while (curr)
	{
		if (curr->program_counter == *color)
		{
			if (on)
				wattron(vm->visu_main, COLOR_PAIR(curr->color + 30) | A_BOLD);
			else
				wattroff(vm->visu_main, COLOR_PAIR(curr->color + 30) | A_BOLD);
		}
		curr = curr->next;
	}
}

static void			move_colors(t_vm *vm, int *color, int on)
{
	t_process	*process;

	process = get_color_process(vm, color);
	if (process)
	{
		if (on)
			wattron(vm->visu_main, COLOR_PAIR(process->color + 10) | A_BOLD);
		else
			wattroff(vm->visu_main, COLOR_PAIR(process->color + 10) | A_BOLD);
	}
	else
	{
		if (on)
			wattron(vm->visu_main,
					COLOR_PAIR(vm->arena_owner[*color] + 20) | A_BOLD);
		else
			wattroff(vm->visu_main,
					COLOR_PAIR(vm->arena_owner[*color] + 20) | A_BOLD);
	}
	vm->arena_moves[*color]--;
}

void				get_color(t_vm *vm, int *color, int on)
{
	t_process	*process;

	if (vm->arena_moves[*color])
		move_colors(vm, color, on);
	else if (vm->arena_owner[*color])
	{
		process = get_color_process(vm, color);
		if (process && on)
			wattron(vm->visu_main, COLOR_PAIR(process->color + 10) | A_BOLD);
		if (process && !on)
			wattroff(vm->visu_main, COLOR_PAIR(process->color + 10) | A_BOLD);
		if (!process && on)
			wattron(vm->visu_main,
					COLOR_PAIR(vm->arena_owner[*color]) | A_BOLD);
		if (!process && !on)
			wattroff(vm->visu_main,
					COLOR_PAIR(vm->arena_owner[*color]) | A_BOLD);
	}
	pc_colors(vm, color, on);
}

void				del_ncurse(t_vm *vm)
{
	clear();
	delwin(vm->visu_main);
	delwin(vm->visu_info);
	delwin(vm->notif);
	delwin(vm->main_border);
	delwin(vm->info_border);
	delwin(vm->notifs_border);
	endwin();
}
