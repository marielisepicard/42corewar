/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_champions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:04:49 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 23:25:14 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_magic_nb(t_vm *vm, char buf[5], int i)
{
	if (((buf[0] & 0xFF) << 24
				| (buf[1] & 0xFF) << 16
				| (buf[2] & 0xFF) << 8
				| (buf[3] & 0xFF)) != 0xea83f3)
	{
		ft_fdprintf(2, "ERROR: File %s has an invalid magic number\n",
				vm->players[i].path);
		exit(EXIT_FAILURE);
	}
}

void	check_champ_code_size(t_vm *vm, const int code_size, const int i)
{
	char	*file;
	int		value;

	if (i < vm->count_players)
	{
		file = vm->players[i].file;
		value = (vm->players[i].file[136] & 0xFF) << 24
			| (vm->players[i].file[137] & 0xFF) << 16
			| (vm->players[i].file[138] & 0xFF) << 8
			| (vm->players[i].file[139] & 0xFF);
		if (value > CHAMP_MAX_SIZE)
			exit_code_size_error(vm, CODE_TOO_LARGE, value, i);
		else if (value != code_size)
			exit_code_size_error(vm, CODE_SIZE_DIFF, value, i);
		vm->players[i].code_size = value;
	}
}

void	fill_player_infos(t_vm *v, int i, int code_size, size_t file_max_size)
{
	ft_bzero(v->players[i].name, PROG_NAME_LENGTH);
	ft_memcpy(v->players[i].name, v->players[i].file + 4, PROG_NAME_LENGTH);
	ft_bzero(v->players[i].comment, COMMENT_LENGTH);
	ft_memcpy(v->players[i].comment, v->players[i].file + 140, COMMENT_LENGTH);
	code_size = code_size - file_max_size + CHAMP_MAX_SIZE;
	check_champ_code_size(v, code_size, i);
	ft_memcpy(v->players[i].code, v->players[i].file + 2192, code_size);
	v->players[i].color = i + 42;
	v->players[i].lives = 0;
	free(v->players[i].file);
}

void	process_buf(t_vm *vm, int ret, int file_max_size, int i)
{
	vm->code_sizes[i] += ret;
	if (vm->code_sizes[i] > file_max_size)
		exit_error(ERROR_FILE_SIZE);
	(vm->code_sizes[i] <= 4) ? check_magic_nb(vm, vm->buf, i) : 0;
	if (!(vm->players[i].file = (char*)realloc(vm->players[i].file,
					vm->code_sizes[i] + 1)))
		exit_error(ERROR_MALLOC);
	ft_bzero(vm->players[i].file + (vm->code_sizes[i] - ret), ret);
	ft_memcpy(vm->players[i].file + (vm->code_sizes[i] - ret),
			vm->buf, ret);
}

void	parse_champions(t_vm *vm, int file_max_size)
{
	int		fd;
	int		ret;
	int		i;
	char	*extension;

	i = 0;
	while (i < vm->count_players)
	{
		extension = ft_strrchr(vm->players[i].path, '.');
		if (ft_strequ(extension, ".cor") == FALSE)
			exit_error(WRONG_EXTENSION);
		if ((fd = open(vm->players[i].path, O_RDONLY)) == FAILURE)
			exit_error(ERROR_OPEN_FILE);
		while ((ret = read(fd, vm->buf, 4)) > 0)
			process_buf(vm, ret, file_max_size, i);
		(ret == FAILURE) || (vm->code_sizes[i] == 0 && ret == 0) ?
			exit_error(ERROR_READ_FILE) : 0;
		fill_player_infos(vm, i, vm->code_sizes[i], file_max_size);
		i++;
	}
	vm->last_alive_name = vm->players[i - 1].name;
	vm->last_alive_number = vm->players[i - 1].number;
}
