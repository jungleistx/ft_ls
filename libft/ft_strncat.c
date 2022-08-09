/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:20:26 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/19 11:17:40 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int				i;
	int				j;
	unsigned long	size;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	size = 0;
	while (size < n)
	{
		if (s2[j] == '\0')
		{
			s1[i] = '\0';
			return (s1);
		}
		s1[i++] = s2[j++];
		size++;
	}
	s1[i] = '\0';
	return (s1);
}
