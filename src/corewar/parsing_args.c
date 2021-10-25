/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:14:45 by manki             #+#    #+#             */
/*   Updated: 2020/02/13 14:04:30 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int8_t	is_player_duplicate(t_vm *vm, int value)
{
	int	i;

	i = 0;
	while (i < vm->count_players)
	{
		if (vm->players[i].number == value)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void		set_player_number(int *player_number, int *i, char **av)
{
	int		nb;

	nb = ft_atoi(av[*i + 1]);
	if (nb > 0 && *player_number == 0)
		*player_number = -nb;
	else
		exit_error("ERROR: too many number for one player");
	*i += 2;
}

static int		set_player_in_vm(t_vm *vm, int *player, char *path,
		int player_number[])
{
	int		nb;

	nb = 0;
	vm->players[*player].path = path;
	if (player_number[*player] == 0)
	{
		nb = -1;
		while (is_player_duplicate(vm, nb) == TRUE)
			nb--;
		player_number[*player] = nb;
	}
	vm->players[*player].number = player_number[*player];
	vm->players[*player].id = *player + 1;
	vm->count_players++;
	*player += 1;
	return (1);
}

static void		init_var(int (*player_nb)[MAX_PLAYERS], int *player, int *i)
{
	ft_bzero(*player_nb, MAX_PLAYERS * sizeof(int));
	*player = 0;
	*i = 1;
}

void			parse_args(int ac, char **av, t_vm *vm)
{
	int		i;
	int		player_nb[MAX_PLAYERS];
	int		player;

	init_var(&player_nb, &player, &i);
	while (i < ac)
	{
		if (ft_strequ(av[i], "-ncurse") == TRUE)
			parse_option_ncurse(vm, &i);
		else if (ft_strequ(av[i], "-c") == TRUE && i++)
			vm->option_v[5] = TRUE;
		else if (ft_strequ(av[i], "-a") == TRUE && i++)
			vm->option_v[6] = TRUE;
		else if (ft_strequ(av[i], "-v") == TRUE && i + 1 < ac)
			parse_option_v(vm, &i, av);
		else if (ft_strequ(av[i], "-dump") == TRUE)
			parse_option_dump(vm, &i, av, ac);
		else if (ft_strequ(av[i], "-n") == TRUE && i + 1 < ac)
			set_player_number(&player_nb[player], &i, av);
		else if (!ft_strequ(av[i], "-v") && !ft_strequ(av[i], "-dump") &&
				!ft_strequ(av[i], "-n") && player < MAX_PLAYERS)
			i += set_player_in_vm(vm, &player, av[i], player_nb);
		else
			exit_args_error(player);
	}
}
