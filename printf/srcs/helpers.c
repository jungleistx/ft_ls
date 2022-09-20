/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:31:56 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/11 12:33:43 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	count_digits(unsigned long long num)
{
	int	res;

	if (num == 0)
		return (1);
	res = 0;
	while (num != 0)
	{
		num /= 10;
		res++;
	}
	return (res);
}

int	ft_putchar_multi(char c, int i)
{
	int	res;

	res = 0;
	while (i-- > 0)
		res += write(1, &c, 1);
	return (res);
}

void	ft_putnbr_l(unsigned long long n)
{
	if (n > 9)
		ft_putnbr_l(n / 10);
	ft_putchar(n % 10 + '0');
}
