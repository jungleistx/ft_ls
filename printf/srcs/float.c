/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:48:44 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 16:30:58 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	float_calc_total(t_info *i)
{
	i->f_total = i->arg_len;
	i->f_total += i->prec;
	if (i->flags & HASH || i->prec > 0)
		i->f_total++;
}

void	print_float_flags(t_info *i)
{
	if (i->flags & SPACE && !(i->flags & NEGATIVE))
	{
		i->res += write(1, " ", 1);
		i->width--;
	}
	if (i->width > i->f_total && !(i->flags & MINUS) && !(i->flags & ZERO))
		i->res += ft_putchar_multi(' ', i->width - i->f_total);
	if (i->flags & NEGATIVE)
		i->res += write(1, "-", 1);
	else if (i->flags & PLUS)
		i->res += write(1, "+", 1);
	if (i->flags & ZERO && i->width > i->f_total)
		i->res += ft_putchar_multi('0', i->width - i->f_total);
}

void	print_float_zero_prec(t_info *i)
{
	if (i->flags & SPACE && !(i->flags & NEGATIVE))
	{
		i->res += write(1, " ", 1);
		i->width--;
	}
	if (i->width > i->arg_len && !(i->flags & ZERO) && !(i->flags & MINUS))
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	if (i->flags & PLUS || (i->flags & NEGATIVE))
	{
		if (i->flags & PLUS && !(i->flags & NEGATIVE))
			i->res += write(1, "+", 1);
		else
			i->res += write(1, "-", 1);
	}
	if (i->width > i->arg_len && i->flags & ZERO)
		i->res += ft_putchar_multi('0', i->width - i->arg_len);
	ft_putnbr_l(i->cur_arg);
	i->res += i->arg_len;
	if (i->flags & MINUS && i->width > i->arg_len)
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
}

void	print_float(t_info *i, va_list args)
{
	unsigned long long	tmp;

	assign_float(i, args);
	if (i->prec == 0)
		return (print_float_zero_prec(i));
	print_float_flags(i);
	ft_putnbr_l(i->cur_arg);
	i->res += i->arg_len;
	if (i->flags & HASH || i->prec > 0)
	i->res += write(1, ".", 1);
	i->res += i->prec;
	while (i->prec-- > 0)
	{
		i->f_arg *= 10;
		tmp = (unsigned long long) i->f_arg;
		i->f_arg -= (long double) tmp;
		ft_putnbr_l(tmp);
	}
	if (i->flags & NEGATIVE)
		i->res--;
	if (i->flags & MINUS && i->width > i->f_total)
		i->res += ft_putchar_multi(' ', i->width - i->f_total);
}
