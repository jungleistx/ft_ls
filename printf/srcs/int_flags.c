/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:44:43 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/11 12:45:22 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_prec_flag(t_info *i)
{
	int	res;

	if (i->flags & ZERO && i->width > i->prec && i->width > i->arg_len)
	{
		if (i->prec > i->arg_len)
			res = ft_putchar_multi('0', i->width - i->prec);
		else
			res = ft_putchar_multi('0', i->width - i->arg_len);
	}
	else
	{
		res = ft_putchar_multi('0', i->prec - i->arg_len);
		i->prec = 0;
	}
	i->width -= res;
	i->res += res;
}

void	print_width(t_info *i)
{
	if (i->flags & ZERO && !(i->flags & DOT))
		return ;
	if (i->flags & NEGATIVE || i->flags & PLUS)
		i->width--;
	if (i->flags & DOT && i->prec > i->arg_len && !(i->flags & ZERO))
	{
		i->res += ft_putchar_multi(' ', i->width - i->prec);
		i->width = 0;
	}
	else if (i->arg_len >= i->prec)
	{
		i->res += ft_putchar_multi(' ', i->width - i->arg_len);
		i->width = 0;
	}
	if (i->flags & ZERO && i->prec > i->arg_len)
	{
		i->res += ft_putchar_multi(' ', i->width - i->prec);
		i->width = 0;
	}
}
