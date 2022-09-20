/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:31:53 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/12 11:23:00 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_percent(t_info *i, va_list args)
{
	(void)args;
	i->width--;
	if (!(i->flags & MINUS) && i->width > 0)
	{
		if (i->flags & ZERO)
			i->res += ft_putchar_multi('0', i->width);
		else
			i->res += ft_putchar_multi(' ', i->width);
	}
	i->res += write(1, "%", 1);
	if (i->flags & MINUS && i->width > 0)
		i->res += ft_putchar_multi(' ', i->width);
}
