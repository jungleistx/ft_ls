/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:55:48 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 11:29:46 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_hex_zero_width(t_info *i)
{
	if (i->flags & DOT)
		i->res += ft_putchar_multi(' ', i->width - i->prec);
	else
	{
		if (i->flags & ZERO)
			i->res += ft_putchar_multi('0', i->width - 1);
		else
			i->res += ft_putchar_multi(' ', i->width - 1);
	}
}

void	print_hex_minus(t_info *i)
{
	if (i->prec > i->arg_len)
		i->res += ft_putchar_multi(' ', i->width - i->prec);
	else
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
}

void	print_hex_hash(t_info *i)
{
	i->res += 2;
	ft_putchar('0');
	ft_putchar(i->hex);
}
