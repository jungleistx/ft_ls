/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:29:42 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/19 17:30:51 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_mid(char const *s)
{
	int	i;
	int	st;

	st = 0;
	while ((s[st] == ' ' || s[st] == '\n' || s[st] == '\t') && s[st] != '\0')
		st++;
	if (s[st] == '\0')
		return (0);
	i = st;
	while (s[i])
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	i++;
	i -= st;
	return (i);
}

char	*ft_strtrim(char const *s)
{
	int		i;
	int		st;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	st = 0;
	while ((s[st] == ' ' || s[st] == '\n' || s[st] == '\t') && s[st] != '\0')
		st++;
	i = count_mid(s);
	ptr = (char *) malloc(i + 1);
	if (!ptr)
		return (NULL);
	ptr[i--] = '\0';
	while (i >= 0)
	{
		ptr[i] = s[i + st];
		i--;
	}
	return (ptr);
}
