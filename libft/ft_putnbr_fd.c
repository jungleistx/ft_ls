/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:47:01 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/12 18:18:22 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	tmp;
	long	copy;

	copy = n;
	if (copy < 0)
	{
		write(fd, "-", 1);
		copy *= -1;
	}
	if (copy > 9)
		ft_putnbr_fd(copy / 10, fd);
	tmp = copy % 10 + '0';
	write(fd, &tmp, 1);
}
