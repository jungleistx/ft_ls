/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:42:25 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/17 10:35:26 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *) s;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			ptr = (char *) &s[i];
			return (ptr);
		}
		i++;
	}
	if (s[i] == c)
	{
		ptr = (char *) &s[i];
		return (ptr);
	}
	return (NULL);
}
