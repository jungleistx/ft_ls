/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:00:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/25 14:15:33 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_notfound(char *filename)
{
	printf("ft_ls: %s: No such file or directory\n", filename);
}

void	exit_usage(void)		//	NOT NEEDED ?
{
	printf("usage: ft_ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	exit(1);
}

void	exit_illegal(void)
{
	printf("ft_ls: illegal option -- -\n");
	// exit_usage();
	printf("usage: ./ft_ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	exit(1);
}

void	exit_malloc_error(char *str)
{
	printf("ERROR with malloc in %s\n", str);		//	LEGIT ERROR??
	exit(2);
}

void	exit_dup_error(char *str)
{
	printf("ERROR with  dup in %s\n", str);			//	LEGIT ERROR??
	exit(3);
}

void	error_dir(char *str)
{
	perror(str);
	exit(4);
}

void	ft_strdup_exit(char *src, t_node *node)
{
	node->name = ft_strdup((const char*)src);
	if (!node->name)
	{
		// strerror() // ?
		exit_dup_error("ft_strdup_exit");
	}
}
