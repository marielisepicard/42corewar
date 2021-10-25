/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:23:59 by manki             #+#    #+#             */
/*   Updated: 2020/02/11 13:30:12 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int8_t	is_number(char *str)
{
	char *p;

	p = str;
	if (*p == '-')
		p++;
	while (*p != '\0')
	{
		if (ft_isdigit(*p) == FALSE)
			return (FALSE);
		p++;
	}
	return (TRUE);
}

void			parse_option_v(t_vm *vm, int *i, char *av[])
{
	int		option_number;

	option_number = 0;
	if (ft_strequ(av[*i], "-v") == 1 && is_number(av[*i + 1])
			&& ft_strlen(av[*i + 1]) < 9 && av[*i + 1][0] != '-')
	{
		option_number = ft_atoi(av[*i + 1]);
		vm->option_v[4] = option_number / 16;
		option_number %= 16;
		vm->option_v[3] = option_number / 8;
		option_number %= 8;
		vm->option_v[2] = option_number / 4;
		option_number %= 4;
		vm->option_v[1] = option_number / 2;
		option_number %= 2;
		vm->option_v[0] = option_number;
		*i += 2;
	}
	else
		*i += 1;
}

void			parse_option_dump(t_vm *vm, int *i, char *av[], int ac)
{
	if (*i + 1 < ac && ft_strequ(av[*i], "-dump") == 1
			&& is_number(av[*i + 1]) && ft_strlen(av[*i + 1]) < 9)
	{
		vm->dump = ft_atoi(av[*i + 1]);
		*i += 2;
	}
	else
	{
		vm->dump = 0;
		*i += 1;
	}
}

void			parse_option_ncurse(t_vm *vm, int *i)
{
	vm->option_ncurse = TRUE;
	*i += 1;
}
