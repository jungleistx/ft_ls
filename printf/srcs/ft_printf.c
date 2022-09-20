/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:54:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/05/18 11:35:33 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	reset_info(t_info *info, int reset)
{
	if (reset == 0)
	{
		info->i = 0;
		info->res = 0;
	}
	info->flags = 0;
	info->f_dec_len = 0;
	info->arg_len = 0;
	info->width = 0;
	info->prec = 1;
	info->hex = 65;
	info->f_arg = 0.0;
	info->cur_arg = 0;
	info->f_total = 0;
}

int	write_non_percent(const char *str, t_info *info)
{
	int	i;

	i = 0;
	while (str[info->i] != '%' && str[info->i] != '\0')
	{
		info->i++;
		i++;
	}
	if (i > 0)
		write(1, &str[info->i - i], i);
	return (i);
}

int	check_flags(const char *str, t_info *info, va_list args, int i)
{
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '+')
			plus_space_flag(&str[i], info);
		else if (ft_isdigit((int)str[i]) || str[i] == '-')
			i += digit_minus_flag(&str[i], info);
		else if (str[i] == '#')
			info->flags |= HASH;
		else if (str[i] == '.' || str[i] == '*')
			i += dot_ast_flag(&str[i], info, args);
		else if (str[i] == 'l' || str[i] == 'L' || str[i] == 'h')
			check_len_flags(str[i], info);
		else if (str[i] == 'j' || str[i] == 't' || str[i] == 'z'
			|| str[i] == 'q')
			special_flags(info);
		else
		{
			info->i += i;
			return (1);
		}
	}
	info->i += i;
	return (0);
}

void	check_specifier(const char *str, t_info *info, va_list args)
{
	int	i;

	i = 0;
	while (SPECS[i])
	{
		if (SPECS[i] == str[0])
		{
			if (SPECS[i] == 'x' || SPECS[i] == 'X')
				info->hex = SPECS[i];
			g_disp_table[i](info, args);
			info->i++;
			return ;
		}
		i++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_info	info;

	reset_info(&info, 0);
	va_start(args, str);
	while (str[info.i])
	{
		if (str[info.i] != '%')
			info.res += write_non_percent(str, &info);
		else
		{
			info.i++;
			if (check_flags(&str[info.i], &info, args, -1))
				check_specifier(&str[info.i], &info, args);
			reset_info(&info, 1);
		}
	}
	va_end(args);
	return (info.res);
}
