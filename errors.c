/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:00:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 15:24:54 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_notfound(char *filename)
{
	printf("ft_ls: %s: No such file or directory\n", filename);
}

void	exit_illegal(void)
{
	printf("ft_ls: illegal option -- -\n");
	printf("usage: ./ft_ls [-alrRt] [file ...]\n");
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
