/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:40:10 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 10:50:48 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*assign_str(t_info *i, va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	i->arg_len = (int)ft_strlen(str);
	if (i->prec > i->arg_len)
		i->prec = i->arg_len;
	else if (i->flags & DOT)
		i->arg_len = i->prec;
	return (str);
}

void	print_str(t_info *i, va_list args)
{
	char	*str;

	str = assign_str(i, args);
	if (!(i->flags & MINUS) && i->width > i->arg_len && i->width > i->prec)
	{
		if (i->flags & ZERO)
		{
			if (i->arg_len >= i->prec)
				i->res += ft_putchar_multi('0', i->width - i->arg_len);
			else
				i->res += ft_putchar_multi('0', i->width - i->prec);
		}
		else if (i->prec >= i->arg_len && i->flags & DOT)
			i->res += ft_putchar_multi(' ', i->width - i->prec);
		else
			i->res += ft_putchar_multi(' ', i->width - i->arg_len);
	}
	i->res += write(1, str, i->arg_len);
	if (i->flags & MINUS && i->width > i->arg_len)
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
}
