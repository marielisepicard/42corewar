/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:21:59 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/25 15:15:56 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

long long	num2(char *str, char *p, int neg)
{
	int j;

	(void)neg;
	j = 0;
	while (*p)
	{
		j++;
		if (*p < '0' || *p > '9')
			return (0);
		if (neg && j > 10)
			return (0x00000000);
		if (!neg && j > 10)
			return (0xFFFFFFFF);
		p++;
	}
	if (j == 10 && neg && ft_strcmp(str + 1, "2147483648") > 0)
		return (0x00000000);
	if (j == 10 && !neg && ft_strcmp(str, "4294967295") > 0)
		return (0xFFFFFFFF);
	return (ft_atol(str));
}

long long	num(char *str)
{
	int		neg;
	char	*p;

	p = str;
	neg = 0;
	if (*p == '-')
	{
		neg = 1;
		p++;
	}
	else if (*p == '+')
		p++;
	if (*p == '\0')
		return (0x00000000);
	return (num2(str, p, neg));
}

int8_t		get_arg_type(t_type type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}
