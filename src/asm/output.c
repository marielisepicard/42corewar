/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:10:32 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/25 11:12:31 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	int2byte(char *s, size_t pos, int32_t value, size_t size)
{
	int8_t	i;

	i = 0;
	while (size)
	{
		s[pos + size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

void	write_bytecode_file(char *filename, t_parsing *p)
{
	char		bytfilename[256];
	char		str[p->output_length];
	int			fd;
	size_t		pos;

	ft_memset(bytfilename, 0, 256);
	ft_strncpy(bytfilename, filename, ft_strlen(filename) - 1);
	ft_strcat(bytfilename, "cor");
	if ((fd = open(bytfilename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == FAILURE)
		exit_error(ERROR_CREATE_FILE);
	ft_printf("Writing output program to %s\n", bytfilename);
	ft_memset(str, 0, p->output_length);
	pos = 0;
	int2byte(str, pos, COREWAR_EXEC_MAGIC, 4);
	pos += 4;
	ft_memcpy(&str[pos], p->prog_name, ft_strlen(p->prog_name));
	pos = pos + PROG_NAME_LENGTH + 4;
	int2byte(str, pos, p->pos, 4);
	pos += 4;
	ft_memcpy(&str[pos], p->comment, ft_strlen(p->comment));
	pos = pos + COMMENT_LENGTH + 4;
	ft_memcpy(&str[pos], p->code, p->pos);
	write(fd, str, p->output_length);
}
