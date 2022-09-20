/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:45:33 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 16:13:01 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_zero_address(t_info *i)
{
	if (!(i->flags & MINUS) && i->width > i->prec)
		i->res += ft_putchar_multi(' ', i->width - i->prec);
	i->res += write(1, "0x", 2);
	if (i->prec != 0)
		i->res += ft_putchar_multi('0', i->prec);
	if (i->flags & MINUS && i->width > i->prec)
		i->res += ft_putchar_multi(' ', i->width - i->prec);
}

void	print_address(t_info *i, va_list args)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
		i->cur_arg = 0;
	else
		i->cur_arg = (unsigned long long)ptr;
	count_hex(i, i->cur_arg);
	i->width -= 2;
	if (i->cur_arg == 0)
		return (print_zero_address(i));
	if (!(i->flags & MINUS) && i->width > i->arg_len)
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	i->res += 2;
	ft_putchar('0');
	ft_putchar('x');
	if (i->flags & DOT)
		i->res += ft_putchar_multi('0', i->prec - i->arg_len);
	print_hex(i->cur_arg, 'a');
	i->res += i->arg_len;
	if (i->flags & MINUS && i->width > i->arg_len)
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
}
