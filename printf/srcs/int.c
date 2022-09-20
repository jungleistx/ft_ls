/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:30:46 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/16 12:37:24 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_prefix_flag(t_info *i)
{
	if (i->flags & NEGATIVE)
		i->res += write(1, "-", 1);
	else
		i->res += write(1, "+", 1);
	i->width--;
}

void	print_zero_number(t_info *i)
{
	if (i->flags & PLUS)
	{
		i->width--;
		if (i->flags & MINUS)
		{
			i->res += write(1, "+", 1);
			i->res += ft_putchar_multi(' ', i->width);
		}
		else
		{
			i->res += ft_putchar_multi(' ', i->width);
			i->res += write(1, "+", 1);
		}
	}
	else if (i->flags & SPACE)
	{
		if (i->width == 0)
			i->width++;
		i->res += ft_putchar_multi(' ', i->width);
	}
	else
		i->res += ft_putchar_multi(' ', i->width);
}

void	print_number(t_info *i, va_list args)
{
	assign_dic(i, args);
	if ((i->cur_arg == 0) && (i->flags & DOT) && (i->prec == 0))
		return (print_zero_number(i));
	if ((i->flags & SPACE) && !(i->flags & NEGATIVE))
	{
		i->res += write(1, " ", 1);
		i->width--;
	}
	if ((i->width > i->arg_len) && (i->width > i->prec) && !(i->flags & MINUS))
		print_width(i);
	if ((i->flags & PLUS) || (i->flags & NEGATIVE))
		print_prefix_flag(i);
	if (((i->flags & ZERO) && (i->width > i->arg_len)) || i->prec > i->arg_len)
		print_prec_flag(i);
	ft_putnbr_l(i->cur_arg);
	i->res += i->arg_len;
	i->width -= i->arg_len;
	if (i->flags & MINUS)
	{
		if (i->width > 0)
			i->res += ft_putchar_multi(' ', i->width);
	}
}
