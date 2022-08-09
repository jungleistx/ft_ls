/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:07:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/17 13:25:59 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*copy;

	copy = (char *)haystack;
	i = 0;
	if (!needle[i])
		return (copy);
	while (copy[i])
	{
		j = 0;
		while (i + j < len && needle[j])
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (haystack[i + j - 1] == needle[j - 1] && needle[j] == '\0')
			return (&copy[i]);
		if (i + j == len && needle[j] != '\0')
			return (NULL);
		i++;
	}
	return (NULL);
}
