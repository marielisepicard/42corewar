/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:24:44 by manki             #+#    #+#             */
/*   Updated: 2020/02/11 18:21:54 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_one_process(t_process *p, char print_registers)
{
	int	i;

	ft_printf("INSIDE t_process [%s]\n", p->name);
	ft_printf("\t name == %s\n", p->name);
	ft_printf("\t number == %d\n", p->number);
	ft_printf("\t program_counter == %d\n", p->program_counter);
	i = -1;
	while (++i < REG_NUMBER && print_registers)
		ft_printf("\t\tregisters[%d] == %d || %x\n", i + 1,
				p->registers[i], p->registers[i]);
	ft_printf("\t carry == %d\n", p->carry);
	ft_printf("\t running == %d\n", p->running);
	ft_printf("\t over == %d\n", p->over);
	ft_printf("\t alive == %d\n", p->alive);
	ft_printf("\t live_calls == %d\n", p->live_calls);
	ft_printf("\t cycle_to_wait : %d\n", p->cycles_to_wait);
	ft_putendl("------------------------------------");
}

void	print_process_list(t_process *p, char print_registers)
{
	t_process	*tmp;

	tmp = p;
	while (tmp)
	{
		print_one_process(tmp, print_registers);
		tmp = tmp->next;
	}
}

/*
** pourquoi 200 ligne 66 ?
*/

void	print_one_player(t_player champ)
{
	int	i;

	ft_printf("\nid : %d\n", champ.id);
	ft_printf("number : %d\n", champ.number);
	ft_printf("NAME  %s\n", champ.name);
	ft_printf("Comment : %s\n", champ.comment);
	ft_printf("file : %s\n", champ.file);
	ft_printf("path : %s\n", champ.path);
	ft_printf("code_size : %s\n", champ.code_size);
	i = -1;
	while (++i < 200)
		ft_printf(" %u%u", champ.code[i] / 16, champ.code[i] % 16);
	ft_putendl("*************************************\n");
}

void	print_player_list(t_vm *vm)
{
	int		i;

	ft_printf("..............PRINTING PLAYER LIST............... \n");
	i = -1;
	while (++i < vm->count_players)
		print_one_player(vm->players[i]);
	ft_printf(".................END PLAYER LIST.................. \n");
}

int		process_list_len(t_process *list)
{
	t_process	*tmp;
	int			len;

	tmp = list;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
