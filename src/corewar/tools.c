/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:28:24 by ekelkel           #+#    #+#             */
/*   Updated: 2020/02/13 17:53:26 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			*fill_tab_sti(int reg)
{
	int		*tab;
	int		i;
	int		j;
	int		k;

	if (!(tab = (int *)malloc(sizeof(int) * 4)))
		exit_error(ERROR_MALLOC);
	i = 3;
	j = 0;
	k = 255;
	while (i >= 0 && j < 4)
	{
		tab[j] = reg >> (i * 8) & k;
		j++;
		i--;
	}
	return (tab);
}

char		check_reg(int reg)
{
	if (reg > 0 && reg <= 16)
		return (TRUE);
	else
		return (FALSE);
}
