/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:03:40 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/17 11:24:49 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int	size;
	int				i;

	i = 0;
	size = 0;
	while (size < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		size++;
	}
	while (size < len)
	{
		dst[i] = '\0';
		i++;
		size++;
	}
	return (dst);
}
