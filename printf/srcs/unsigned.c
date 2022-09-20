/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:38:14 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 17:13:55 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_zero_unsig(t_info *i)
{
	if (i->width > 0)
		i->res += ft_putchar_multi(' ', i->width);
}

void	print_unsigned_width(t_info *i)
{
	if (!(i->flags & MINUS) && (i->width > i->arg_len && i->width > i->prec))
	{
		if (i->flags & DOT && i->prec > i->arg_len)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else if (i->flags & ZERO && !(i->flags & DOT))
			i->res += ft_putchar_multi('0', i->width - i->arg_len);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
}

void	print_unsigned(t_info *i, va_list args)
{
	assign_oux(i, args);
	i->arg_len = count_digits(i->cur_arg);
	if (i->prec == 0 && i->cur_arg == 0)
		return (print_zero_unsig(i));
	print_unsigned_width(i);
	if (i->prec > i->arg_len)
		i->res += ft_putchar_multi('0', i->prec - i->arg_len);
	i->res += i->arg_len;
	ft_putnbr_l(i->cur_arg);
	if (i->flags & MINUS && i->width > i->arg_len && i->width > i->prec)
	{
		if (i->prec > i->arg_len)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
}

void	print_unsigned_long(t_info *i, va_list args)
{
	if ((i->flags & LONG) && !(i->flags & LLONG))
		i->flags |= LLONG;
	else if (!(i->flags & LONG))
		i->flags |= LONG;
	return (print_unsigned(i, args));
}
