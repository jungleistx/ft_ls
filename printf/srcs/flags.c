/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:27:23 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/19 11:27:40 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	special_flags(t_info *i)
{
	if (i->flags & LONG && !(i->flags & LLONG))
		i->flags |= LLONG;
	else if (!(i->flags & LONG))
		i->flags |= LONG;
}

void	check_len_flags(char c, t_info *info)
{
	if (c == 'L' && !(info->flags & FLONG))
		info->flags |= FLONG;
	else if (c == 'l')
	{
		if (info->flags & LONG && !(info->flags & LLONG))
			info->flags |= LLONG;
		else if (!(info->flags & LONG))
			info->flags |= LONG;
	}
	else if (c == 'h')
	{
		if (info->flags & SHORT && !(info->flags & SSHORT))
			info->flags |= SSHORT;
		else if (!(info->flags & SHORT))
			info->flags |= SHORT;
	}
}

int	digit_minus_flag(const char *str, t_info *info)
{
	int	i;

	i = 0;
	if (str[i] == '0')
		info->flags |= ZERO;
	else if (str[i] == '-')
		info->flags |= MINUS;
	else
	{
		info->width = ft_atoi(&str[i]);
		i = count_digits((long long)info->width);
		i--;
	}
	if ((info->flags & MINUS) && (info->flags & ZERO))
		info->flags ^= ZERO;
	if (info->width < 0)
	{
		info->width *= -1;
		info->flags |= MINUS;
		if (info->flags & ZERO)
			info->flags ^= ZERO;
	}
	return (i);
}

void	plus_space_flag(const char *str, t_info *i)
{
	if (str[0] == '+')
		i->flags |= PLUS;
	else
		i->flags |= SPACE;
	if ((i->flags & PLUS) && (i->flags & SPACE))
		i->flags ^= SPACE;
}
