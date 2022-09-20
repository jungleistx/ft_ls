/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:46:39 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 15:23:14 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	calc_printed(t_info *i, va_list args)
{
	long long	*lptr;
	signed char	*cptr;
	int			*iptr;

	iptr = NULL;
	cptr = NULL;
	lptr = NULL;
	if (i->flags & LLONG)
	{
		lptr = va_arg(args, long long *);
		*lptr = (long long)i->res;
	}
	else if (i->flags & SSHORT)
	{
		cptr = va_arg(args, signed char *);
		*cptr = (signed char)i->res;
	}
	else
	{
		iptr = va_arg(args, int *);
		*iptr = i->res;
	}
}

void	print_binary_value(t_info *i, unsigned long long num)
{
	char	tmp;

	if (num >= 2)
		print_binary_value(i, num / 2);
	tmp = num % 2 + '0';
	i->res += write(1, &tmp, 1);
}

void	print_binary(t_info *i, va_list args)
{
	i->cur_arg = va_arg(args, unsigned long long);
	print_binary_value(i, i->cur_arg);
}

void	print_uppercase_number(t_info *i, va_list args)
{
	if (i->flags & LONG && !(i->flags & LLONG))
		i->flags |= LLONG;
	else if (!(i->flags & LONG) && !(i->flags & LLONG))
		i->flags |= LONG;
	print_number(i, args);
}
