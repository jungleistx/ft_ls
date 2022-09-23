/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:00:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/23 18:56:58 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	error_notfound(char *filename)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	exit_illegal(void)
{
	ft_putstr_fd("ft_ls: illegal option -- -\n", 2);
	ft_putstr_fd("usage: ./ft_ls [-alrRt] [file ...]\n", 2);
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
