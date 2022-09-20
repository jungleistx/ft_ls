/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:43:59 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/16 12:32:27 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_zero_octal_flags(t_info *i)
{
	if (!(i->flags & MINUS && i->width > 0) && i->width > i->prec)
	{
		if (i->flags & ZERO && i->prec != 0 && i->arg_len > i->prec)
			i->res += ft_putchar_multi('0', i->width - i->arg_len);
		else if (i->flags & DOT && i->width > i->prec && i->prec > 0)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else if (i->flags & ZERO && i->prec != 0)
			i->res += ft_putchar_multi('0', i->width - i->arg_len);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
}

void	print_zero_octal(t_info *i)
{
	if (!(i->flags & HASH) && i->width < 1 && i->prec == 0)
		return ;
	if (i->prec == 0 && !(i->flags & HASH))
		i->arg_len = 0;
	print_zero_octal_flags(i);
	if (i->flags & DOT)
		i->res += ft_putchar_multi('0', i->prec - 1);
	if (i->flags & HASH || i->prec > 0)
		i->res += write(1, "0", 1);
	if (i->flags & MINUS && i->width > 1 && i->width > i->prec)
	{
		if (i->flags & DOT && i->prec > 0)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
}
