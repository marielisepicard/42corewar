/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:18:38 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 14:46:23 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_hex_mem(t_vm *v, char *add, size_t size, int *color)
{
	size_t		i;
	char		*hex;

	hex = "0123456789abcdef";
	i = 0;
	while (i < 64)
	{
		if (i < size)
		{
			get_color(v, color, 1);
			wprintw(v->visu_main, "%c", hex[(int)((unsigned char)add[i]) / 16]);
			wprintw(v->visu_main, "%c", hex[(int)((unsigned char)add[i]) % 16]);
			get_color(v, color, 0);
		}
		if (i % 2)
			wprintw(v->visu_main, " ");
		i++;
		*color += 1;
	}
}

void		dump_ncurse(t_vm *vm, unsigned char arena[], size_t size)
{
	int		offset;
	int		champ_color;

	offset = 0;
	champ_color = 0;
	while (size > 64)
	{
		print_hex_mem(vm, (char *)arena + offset, 64, &champ_color);
		wprintw(vm->visu_main, "\n");
		offset += 64;
		size -= 64;
	}
	print_hex_mem(vm, (char *)arena + offset, size, &champ_color);
	wprintw(vm->visu_main, "\n");
}

static void	reload_info(t_vm *vm)
{
	werase(vm->visu_info);
	print_infos(vm);
	print_champ_infos(vm);
	wnoutrefresh(vm->visu_info);
}

static void	reload_notifs(t_vm *vm)
{
	if (vm->cpt_notifs == (unsigned int)(LINES / 3) - 4)
	{
		werase(vm->notif);
		vm->cpt_notifs = 0;
	}
	wnoutrefresh(vm->notif);
	vm->cpt_notifs++;
}

void		reload_windows(t_vm *vm, int nb)
{
	if (nb == 1)
	{
		werase(vm->visu_main);
		dump_ncurse(vm, vm->arena, MEM_SIZE);
		wnoutrefresh(vm->visu_main);
	}
	else if (nb == 2)
		reload_info(vm);
	else if (nb == 3)
		reload_notifs(vm);
	doupdate();
	usleep(vm->usleep);
}
