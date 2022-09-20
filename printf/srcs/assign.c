/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:33:38 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/17 15:44:33 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	assign_dic(t_info *i, va_list args)
{
	long long	temp;

	if (i->flags & LLONG)
		temp = va_arg(args, long long);
	else if (i->flags & LONG)
		temp = (long long) va_arg(args, long);
	else if (i->flags & SSHORT)
		temp = (long long)(signed char) va_arg(args, int);
	else if (i->flags & SHORT)
		temp = (long long)(short) va_arg(args, int);
	else
		temp = (long long) va_arg(args, int);
	if (temp < 0)
	{
		i->flags |= NEGATIVE;
		i->cur_arg = temp * -1;
	}
	else
		i->cur_arg = (unsigned long long)temp;
	i->arg_len = count_digits(i->cur_arg);
}

void	assign_oux(t_info *i, va_list args)
{
	if (i->flags & LLONG)
		i->cur_arg = va_arg(args, unsigned long long);
	else if (i->flags & LONG)
		i->cur_arg = (unsigned long long) va_arg(args, unsigned long);
	else if (i->flags & SSHORT)
		i->cur_arg = (unsigned long long)(unsigned char)
			va_arg(args, unsigned int);
	else if (i->flags & SHORT)
		i->cur_arg = (unsigned long long)(unsigned short)
			va_arg(args, unsigned int);
	else
		i->cur_arg = (unsigned long long) va_arg(args, unsigned int);
}

int	check_rounding(long double frac, int prec)
{
	unsigned long long	tmp;

	tmp = (unsigned long long) frac;
	frac -= (long double)tmp;
	while (prec-- > 0)
	{
		frac *= 10;
		tmp = (unsigned long long)frac;
		frac -= (long double) tmp;
	}
	if (frac == (long double) 0.5)
	{
		if (tmp % 2 != 0)
			return (1);
	}
	else if (frac > (long double) 0.5)
	{
		return (1);
	}
	return (0);
}

void	assign_float_to_ints(long double frac, t_info *i, int prec)
{
	long double	x;

	x = 1.0;
	while (prec-- > 0)
		x /= 10;
	if (check_rounding(frac, i->prec))
		frac += x;
	i->cur_arg = (unsigned long long)frac;
	i->arg_len = count_digits(i->cur_arg);
	if (i->flags & NEGATIVE || i->flags & PLUS)
		i->arg_len++;
	frac -= (long double) i->cur_arg;
	i->f_arg = frac;
	i->f_dec_len = i->prec;
	float_calc_total(i);
}

void	assign_float(t_info *i, va_list args)
{
	if (i->flags & FLONG)
		i->f_arg = va_arg(args, long double);
	else
		i->f_arg = (long double) va_arg(args, double);
	if (1 / i->f_arg < 0)
	{
		i->f_arg *= -1;
		i->flags |= NEGATIVE;
	}
	if (!(i->flags & DOT))
		i->prec = 6;
	assign_float_to_ints(i->f_arg, i, i->prec);
}
