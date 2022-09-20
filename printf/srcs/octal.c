/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:19:16 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/12 13:08:55 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_octal_non_minus(t_info *i)
{
	if (i->flags & HASH && i->prec <= i->arg_len)
		i->width--;
	if (i->flags & ZERO && i->prec > i->arg_len)
		i->res += ft_putchar_multi('0', i->width - i->prec);
	else if (i->flags & ZERO && !(i->flags & DOT))
		i->res += ft_putchar_multi('0', i->width - i->arg_len);
	else if (i->prec > i->arg_len)
		i->res += ft_putchar_multi(' ', i->width - i->prec);
	else
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
}

void	print_octal_minus(t_info *i)
{
	if (i->width > i->prec && i->width > i->arg_len)
	{
		if (i->prec > i->arg_len)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
}

void	count_octal(t_info *i, unsigned long long tmp)
{
	while (tmp >= 0)
	{
		if (tmp < 8)
		{
			i->arg_len++;
			return ;
		}
		tmp /= 8;
		i->arg_len++;
	}
}

void	print_octal_numbers(t_info *i, unsigned long long a)
{
	if (a >= 8)
		print_octal_numbers(i, a / 8);
	ft_putchar(a % 8 + '0');
}

void	print_octal(t_info *i, va_list args)
{
	assign_oux(i, args);
	count_octal(i, i->cur_arg);
	if (i->cur_arg == 0)
		return (print_zero_octal(i));
	if (i->width > i->prec && i->width > i->arg_len && !(i->flags & MINUS))
		print_octal_non_minus(i);
	if (i->flags & HASH)
	{
		i->res += write(1, "0", 1);
		i->prec--;
		i->width--;
	}
	if (i->prec > i->arg_len)
		i->res += ft_putchar_multi('0', i->prec - i->arg_len);
	print_octal_numbers(i, i->cur_arg);
	i->res += i->arg_len;
	if (i->flags & MINUS)
		print_octal_minus(i);
}
