/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:47:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/17 13:35:54 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	letter;
	char	*copy;

	letter = c;
	copy = (char *)s;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (copy[i] == letter)
			return (&copy[i]);
		i--;
	}
	if (copy[i] == letter)
		return (&copy[i]);
	else
		return (NULL);
}
