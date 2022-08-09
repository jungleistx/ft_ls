/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:07:14 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/19 10:44:46 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*copy;

	copy = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (copy[i] == (unsigned char)c)
			return (&copy[i]);
		i++;
	}
	return (NULL);
}
