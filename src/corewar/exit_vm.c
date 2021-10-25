/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:08:59 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 21:03:27 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <errno.h>

void	free_process(t_process *list)
{
	t_process	*cursor;

	cursor = list;
	list = list->next;
	while (cursor && cursor->next)
	{
		cursor->next = list->next;
		if (list)
			free(list);
		list = cursor->next;
	}
	if (cursor)
		free(cursor);
}

void	free_vm(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < vm->count_players)
	{
		if (vm->players[i].file)
			free(vm->players[i].file);
		if (vm->players[i].path)
			free(vm->players[i].path);
		i++;
	}
	free_process(vm->process_list);
	del_ncurse(vm);
	free(vm);
}

void	exit_args_error(int player)
{
	(player >= MAX_PLAYERS) ?
		exit_error("ERROR: too many champions")
		: exit_error("ERROR: wrong arguments, see usage");
}

void	exit_code_size_error(t_vm *vm, int8_t error, int code_size, int player)
{
	if (error == CODE_TOO_LARGE)
	{
		ft_fdprintf(2, "Error: File %s has too large a code ",
					vm->players[player].path);
		ft_fdprintf(2, "(%d bytes > %d bytes)\n", code_size,
					CHAMP_MAX_SIZE);
	}
	else if (error == CODE_TOO_SMALL)
	{
		ft_fdprintf(2, "Error: File %s is too small to be a champion\n",
					vm->players[player].path);
		exit(EXIT_FAILURE);
	}
	else if (error == CODE_SIZE_DIFF)
	{
		ft_fdprintf(2, "Error: File %s has a code size that differ ",
					vm->players[player].path);
		ft_fdprintf(2, "from what its header says\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	exit_error(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit(EXIT_FAILURE);
}
