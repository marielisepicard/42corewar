/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:09:25 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/02 13:37:12 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memset() function writes len bytes of value c (converted to an unsigned
** char) to the string b.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *dst;

	if (!b)
		return (NULL);
	dst = (unsigned char *)b;
	while (len-- > 0)
		*dst++ = (unsigned char)c;
	return (b);
}
