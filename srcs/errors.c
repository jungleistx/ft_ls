/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:00:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/20 15:45:49 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	error_notfound(char *filename)
{
	ft_printf("ft_ls: %s: No such file or directory\n", filename);
}

void	exit_illegal(void)
{
	ft_printf("ft_ls: illegal option -- -\n");
	ft_printf("usage: ./ft_ls [-alrRt] [file ...]\n");
	exit(1);
}

void	exit_malloc_error(char *str)
{
	perror(str);
	exit(2);
}

void	exit_dup_error(char *str)
{
	perror(str);
	exit(3);
}

void	error_dir(char *str)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(str);
}
