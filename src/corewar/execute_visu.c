/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_visu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:52:11 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 21:59:32 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_infos(t_vm *vm)
{
	int		cols_info;

	cols_info = COLS / 3;
	wattron(vm->visu_info, COLOR_PAIR(1) | A_BOLD);
	wprintw(vm->visu_info, "%*s\n", ((cols_info - 3) / 2) + 11,
			"- INFORMATIONS -");
	wprintw(vm->visu_info, "Press the space key to pause and restart the ");
	wprintw(vm->visu_info, "game and press Q to exit.\n");
	wattroff(vm->visu_info, COLOR_PAIR(1) | A_BOLD);
	wprintw(vm->visu_info, "Cycle : ");
	wattron(vm->visu_info, COLOR_PAIR(1) | A_BOLD);
	wprintw(vm->visu_info, "%d\n", vm->cycles);
	wattroff(vm->visu_info, COLOR_PAIR(1) | A_BOLD);
	wprintw(vm->visu_info, "Number of Champion(s) : ");
	wattron(vm->visu_info, COLOR_PAIR(1) | A_BOLD);
	wprintw(vm->visu_info, "%d\n", vm->count_players);
	wattroff(vm->visu_info, COLOR_PAIR(1) | A_BOLD);
	wprintw(vm->visu_info, "%*s\n", ((cols_info - 3) / 2) + 11,
			"- CONTESTANTS -");
}

void	print_champ_infos(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < vm->count_players)
	{
		wprintw(vm->visu_info, "Champion ");
		wattron(vm->visu_info, COLOR_PAIR(vm->players[i].color) | A_BOLD);
		wprintw(vm->visu_info, "%s", vm->players[i].name);
		wattroff(vm->visu_info, COLOR_PAIR(vm->players[i].color) | A_BOLD);
		wprintw(vm->visu_info, ": \n");
		wprintw(vm->visu_info, "\tLives :\t\t%d\n", vm->players[i].lives);
		i++;
	}
}
