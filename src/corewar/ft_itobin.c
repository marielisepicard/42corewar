/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itobin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 10:33:37 by mpicard           #+#    #+#             */
/*   Updated: 2020/02/13 14:29:53 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
**	La fonction ft_itobin prend un int en parametre (l'opcode d'une instruction)
**	et renvoie son binaire
**	en chaines de caractere. On envoie cette str dans une des fonction
**	find_special_pc pour qu'on sache "combien" de bit on attend d'une instructio
**	EXEMPLE : on a l'instruction "0b 36 01 01 01 01 01 01 01... ".
**	36 en binaire = 00 11 01 10
**	00 -> rien , 11 -> indirect (2 bytes), 01 -> registre ( 1 byte ),
**	10 -> registre ( 4 bytes)
**	C'est necessaire d'avoir cette information dans les cas ou on a une
**	instruction avec
**	un mauvais op code. (gestion des cas d'erreur)
**	(ML - 02.02.20)
**
**	les deux fonctions sont particuliere, il y a des cas ou on ne doit regarder
**	que les 2 premiers "arguments", je ne comprends pas la logique mais ca
**	fonctionne...
*/

int		find_special_pc_quarte(t_vm *vm)
{
	int		res;

	res = 0;
	if (ft_strequ(vm->ocp[0], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[1], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[2], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[2], _DIR))
		res += 2;
	else if (ft_strequ(vm->ocp[2], _REG))
		res += 1;
	res += 2;
	return (res);
}

int		find_special_pc_terce(t_vm *vm)
{
	int		res;

	res = 0;
	if (ft_strequ(vm->ocp[0], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		res += 4;
	else if (ft_strequ(vm->ocp[0], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[1], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		res += 4;
	else if (ft_strequ(vm->ocp[1], _REG))
		res += 1;
	res += 2;
	return (res);
}

/*
** dans le cas ou le direct va etre code que sur 2 bytes (ex : sti)
*/

int		find_special_pc_bis(t_vm *vm)
{
	int		res;

	res = 0;
	if (ft_strequ(vm->ocp[0], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[1], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[2], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[2], _DIR))
		res += 2;
	else if (ft_strequ(vm->ocp[2], _REG))
		res += 1;
	res += 2;
	return (res);
}

/*
** 	cas classique
**
** 	j'ai mis en commentaire le check du dernier octet car cela m'a permis
** 	de fix le bugg avec add dans tests/vm/overflow/zjmp_neg_overflow_fail
** 	d'ailleur dans le sujet il est dit que l'opcode est code sur 3 octet et que
** 	le dernier est a zero, est-ce qu'il faut vraiment chequer le dernier byte
** 	du coup ? (manki)
*/

int		find_special_pc(t_vm *vm)
{
	int		res;

	res = 0;
	if (ft_strequ(vm->ocp[0], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[0], _DIR))
		res += 4;
	else if (ft_strequ(vm->ocp[0], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[1], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[1], _DIR))
		res += 4;
	else if (ft_strequ(vm->ocp[1], _REG))
		res += 1;
	if (ft_strequ(vm->ocp[2], _IND))
		res += 2;
	else if (ft_strequ(vm->ocp[2], _DIR))
		res += 4;
	else if (ft_strequ(vm->ocp[2], _REG))
		res += 1;
	res += 2;
	return (res);
}

void	ft_itobin(t_vm *vm, int nb)
{
	int		i;
	int		var;

	i = 0;
	ft_memset(&vm->ocp[0], 0, 3);
	ft_memset(&vm->ocp[1], 0, 3);
	ft_memset(&vm->ocp[2], 0, 3);
	ft_memset(&vm->ocp[3], 0, 3);
	while (i < 8)
	{
		var = vm->tab_pow[7 - i];
		if (nb / var)
			vm->ocp[i / 2][i % 2] = '1';
		else
			vm->ocp[i / 2][i % 2] = '0';
		nb %= var;
		i++;
	}
}
