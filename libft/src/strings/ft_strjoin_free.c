/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:55:28 by agelloz           #+#    #+#             */
/*   Updated: 2020/01/26 21:48:34 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne une chaîne de caractères
** “fraiche” terminée par un ’\0’ résultant de la concaténation
** de s1 et s2. Free s1. Si l’allocation echoue, la fonction renvoie NULL.
*/

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(result = ft_strnew((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (result);
}
