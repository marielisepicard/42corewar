/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:26:16 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 19:18:28 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_init_colors(void)
{
	init_color(42, 499, 865, 297);
	init_color(43, 1000, 862, 275);
	init_color(44, 981, 642, 375);
	init_color(45, 985, 542, 995);
	init_color(52, 297, 665, 99);
	init_color(53, 801, 662, 73);
	init_color(54, 781, 442, 175);
	init_color(55, 785, 340, 794);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(42, 42, COLOR_BLACK);
	init_pair(43, 43, COLOR_BLACK);
	init_pair(44, 44, COLOR_BLACK);
	init_pair(45, 45, COLOR_BLACK);
	init_pair(52, COLOR_BLACK, 7);
	init_pair(53, COLOR_BLACK, 7);
	init_pair(54, COLOR_BLACK, 7);
	init_pair(55, COLOR_BLACK, 7);
	init_pair(62, 52, COLOR_BLACK);
	init_pair(63, 53, COLOR_BLACK);
	init_pair(64, 54, COLOR_BLACK);
	init_pair(65, 55, COLOR_BLACK);
	init_pair(72, COLOR_BLACK, 42);
	init_pair(73, COLOR_BLACK, 43);
	init_pair(74, COLOR_BLACK, 44);
	init_pair(75, COLOR_BLACK, 45);
}

static void	init_ncurse2(void)
{
	ft_init_colors();
	noecho();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	refresh();
}

void		init_ncurse(t_vm *vm)
{
	int		c_main;
	int		c_info;
	int		l_info;
	int		l_notif;

	initscr();
	c_main = 2 * COLS / 3;
	c_info = COLS / 3;
	l_info = 2 * LINES / 3;
	l_notif = LINES / 3;
	vm->main_border = subwin(stdscr, LINES, c_main, 0, 0);
	vm->info_border = subwin(stdscr, l_info, c_info, 0, c_main);
	vm->notifs_border = subwin(stdscr, l_notif + 1, c_info, l_info, c_main);
	vm->visu_main = subwin(stdscr, LINES - 2, c_main - 3, 1, 2);
	vm->visu_info = subwin(stdscr, l_info - 2, c_info - 3, 1, c_main + 2);
	vm->notif = subwin(stdscr, l_notif - 4, c_info - 3, l_info + 1, c_main + 2);
	box(vm->main_border, ACS_VLINE, ACS_HLINE);
	box(vm->info_border, ACS_VLINE, ACS_HLINE);
	box(vm->notifs_border, ACS_VLINE, ACS_HLINE);
	start_color();
	init_color(COLOR_BLACK, 125, 125, 125);
	init_ncurse2();
}

void		pause_game(void)
{
	int		key;

	while (1)
	{
		key = getch();
		if (key == ' ')
			break ;
		else if (key == 'q')
			exit(0);
	}
}

void		get_key(void)
{
	int				key;

	key = getch();
	if (key == ' ')
		pause_game();
	else if (key == 'q')
		exit(0);
}
