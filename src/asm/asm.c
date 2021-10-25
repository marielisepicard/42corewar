/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:10:32 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/26 20:05:48 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void	assemble_source_code(char *filename)
{
	t_lexing	s;
	t_parsing	p;

	if ((s.fd = open(filename, O_RDONLY)) == FAILURE)
		exit_error(ERROR_OPEN_FILE);
	lex_source_code(&s);
	parse_source_code(&s, &p);
	write_bytecode_file(filename, &p);
	free_s(&s, &p);
}

int			main(int ac, char **av)
{
	int		fd;
	char	*extension;

	if (ac == 2)
	{
		errno = 0;
		extension = ft_strrchr(av[1], '.');
		if (ft_strequ(extension, ".s") == FALSE)
			exit_error(WRONG_EXTENSION);
		if ((fd = open(av[1], O_RDONLY)) == FAILURE)
			exit_error(ERROR_OPEN_FILE);
		if (ft_strlen(av[1]) > 253)
			exit_error(FILE_NAME_TOO_LONG);
		assemble_source_code(av[1]);
	}
	else
		ft_printf("Usage: ./asm <champion.s>\n");
	return (EXIT_SUCCESS);
}
