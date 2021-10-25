/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:34:30 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/10 18:28:18 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	free_ps_list(t_process **alst)
{
	if (*alst)
	{
		free_ps_list(&(*alst)->next);
		free(*alst);
		*alst = NULL;
	}
}

void		dump_arena(t_vm *vm)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = "0123456789abcdef";
	while (i < MEM_SIZE)
	{
		if (!(i % ARENA_LINE_SIZE))
		{
			if (i != 0)
				ft_putchar('\n');
			ft_printf("0x0%.3x : ", j);
			j += 64;
		}
		ft_printf("%c", str[vm->arena[(i) % MEM_SIZE] / 16]);
		ft_printf("%c ", str[vm->arena[(i) % MEM_SIZE] % 16]);
		i++;
	}
	free_ps_list(&vm->process_list);
	ft_putchar('\n');
}
