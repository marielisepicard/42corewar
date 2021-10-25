/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtualmachine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:28:51 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/13 14:05:32 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N -v N -c | -ncurse] [[-n number] ");
	ft_printf("champion1.cor] ...\n");
	ft_printf("#### TEXT OUTPUT MODE ########################################");
	ft_printf("##################\n");
	ft_printf("\t-dump N\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-v N\t: Verbosity levels, can be added together to enable ");
	ft_printf("several\n");
	ft_printf("\t\t\t- 0 : Show only essentials\n");
	ft_printf("\t\t\t- 1 : Show lives\n");
	ft_printf("\t\t\t- 2 : Show cycles\n");
	ft_printf("\t\t\t- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("\t\t\t- 8 : Show deaths\n");
	ft_printf("\t\t\t- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("\t-c  \t: Color, shows verbose with colors\n");
	ft_printf("#### NCURSES OUTPUT MODE #####################################");
	ft_printf("##################\n");
	ft_printf("\t-ncurse\t: Ncurses output mode\n");
	ft_printf("##############################################################");
	ft_printf("##################\n");
	exit(EXIT_SUCCESS);
}

static void	print_intro_message(t_vm *vm)
{
	int	i;

	if (vm->option_ncurse == TRUE)
		return ;
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->count_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1, vm->players[i].code_size, vm->players[i].name,
				vm->players[i].comment);
		i++;
	}
}

static void	fill_arena(t_vm *vm)
{
	int				player_nb;
	int				position;
	int				i;
	int				j;
	unsigned char	*arena;

	player_nb = vm->count_players;
	arena = vm->arena;
	position = 0;
	i = 0;
	while (i < player_nb)
	{
		j = position;
		while (j < (position + vm->players[i].code_size))
		{
			arena[j] = vm->players[i].code[j - position];
			vm->arena_owner[j] = vm->players[i].color;
			j++;
		}
		i++;
		position += (MEM_SIZE / vm->count_players);
	}
}

void		set_tab_pow(t_vm *vm)
{
	long	i;

	i = 0;
	vm->tab_pow[0] = 1;
	while (++i < 8)
		vm->tab_pow[i] = vm->tab_pow[i - 1] * 2;
}

int			main(int ac, char **av)
{
	t_vm	*vm;
	int		file_max_size;

	if (ac == 1)
		print_usage();
	errno = 0;
	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		exit_error("MALLOC FAILED");
	initialize_vm(vm, av);
	parse_args(ac, av, vm);
	file_max_size = PROG_NAME_LENGTH + CHAMP_MAX_SIZE + COMMENT_LENGTH + 16;
	parse_champions(vm, file_max_size);
	fill_arena(vm);
	init_players_processes(vm);
	(vm->option_ncurse == TRUE) ? ft_bzero(vm->option_v, 5) : 0;
	(vm->option_ncurse == TRUE) ? init_ncurse(vm) : 0;
	print_intro_message(vm);
	launch_fight(vm);
	free(vm);
	return (EXIT_SUCCESS);
}
