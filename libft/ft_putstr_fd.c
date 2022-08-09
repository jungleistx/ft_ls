/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:31:15 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/19 19:17:53 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int		i;
	char	*ptr;

	if (s == NULL)
		return ;
	i = 0;
	ptr = (char *)s;
	while (ptr[i])
	{
		write(fd, &ptr[i], 1);
		i++;
	}
}
