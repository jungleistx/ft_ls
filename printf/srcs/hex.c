/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:41:53 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 17:28:48 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_zero_hex(t_info *i)
{
	if (i->prec == 0)
		i->res += ft_putchar_multi(' ', i->width);
	else if (i->prec >= i->width)
		i->res += ft_putchar_multi('0', i->prec);
	else
	{
		if (!(i->flags & MINUS && i->width > 1))
			print_hex_zero_width(i);
		if (i->prec > 0)
			i->res += ft_putchar_multi('0', i->prec - 1);
		i->res += write(1, "0", 1);
		if (i->flags & MINUS && i->width > 1)
		{
			if (i->flags & DOT)
				i->res += ft_putchar_multi(' ', i->width - i->prec);
			else
				i->res += ft_putchar_multi(' ', i->width - 1);
		}
	}
}

void	count_hex(t_info *i, unsigned long long tmp)
{
	while (tmp >= 0)
	{
		if (tmp < 16)
		{
			i->arg_len++;
			return ;
		}
		tmp /= 16;
		i->arg_len++;
	}
}

void	print_hex(unsigned long long i, char letter)
{
	if (i > 15)
	{
		print_hex(i / 16, letter);
		if (i % 16 > 9)
			ft_putchar(i % 16 - 10 + letter);
		else
			ft_putchar(i % 16 + '0');
	}
	else
	{
		if (i > 9)
			ft_putchar(i % 10 + letter);
		else
			ft_putchar(i + '0');
	}
}

void	print_hex_width(t_info *i)
{
	if (!(i->flags & ZERO) && i->width > i->prec && i->width > i->arg_len)
	{
		if (i->prec > i->arg_len)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
	if (i->flags & ZERO && i->width > i->prec && i->width > i->arg_len)
	{
		if (i->prec > i->arg_len)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else if (i->flags & DOT)
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
		else
		{
			if (i->flags & HASH)
			{
				print_hex_hash(i);
				i->flags ^= HASH;
			}
			i->res += ft_putchar_multi('0', i->width - i->arg_len);
		}
		i->width = 0;
	}
}

void	print_hex_flags(t_info *i, va_list args)
{
	assign_oux(i, args);
	count_hex(i, i->cur_arg);
	if (i->cur_arg == 0)
		return (print_zero_hex(i));
	if (i->flags & HASH)
		i->width -= 2;
	if (!(i->flags & MINUS))
		print_hex_width(i);
	if (i->flags & HASH)
		print_hex_hash(i);
	if (!(i->flags & MINUS) && i->width > i->arg_len && i->width > i->prec)
	{
		if (i->flags & ZERO)
			i->res += ft_putchar_multi('0', i->width - i->arg_len);
	}
	if (i->prec > i->arg_len)
		i->res += ft_putchar_multi('0', i->prec - i->arg_len);
	print_hex(i->cur_arg, i->hex - 23);
	i->res += i->arg_len;
	if (i->flags & MINUS && i->width > i->arg_len && i->width > i->prec)
		print_hex_minus(i);
}
