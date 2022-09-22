/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:34:34 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/22 14:43:12 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	list_add_long_filetype(t_node *node, struct stat filestat, int a)
{
	ft_memset((void *)node->l_opt->permissions, '-', 10);
	if (node->type == 4)
		node->l_opt->permissions[0] = 'd';
	else if (node->type == 10)
		node->l_opt->permissions[0] = 'l';
	else if (node->type == 2)
		node->l_opt->permissions[0] = 'c';
	else if (node->type == 3)
		node->l_opt->permissions[0] = 'b';
	else
		node->l_opt->permissions[0] = '-';
	while (--a >= 0)
	{
		if (filestat.st_mode & (1 << a))
		{
			if (a == 8 || a == 5 || a == 2)
				node->l_opt->permissions[(a - 9) * -1] = 'r';
			else if (a == 7 || a == 4 || a == 1)
				node->l_opt->permissions[(a - 9) * -1] = 'w';
			else if (a == 6 || a == 3 || a == 0)
				node->l_opt->permissions[(a - 9) * -1] = 'x';
		}
	}
	node->l_opt->permissions[10] = '\0';
}

void	exit_readlink_error(char *str)
{
	perror(str);
	exit (5);
}

void	print_sym_link(t_node *node, int opts)
{
	struct stat	filestat;
	char		buf[257];

	ft_bzero((void *)buf, (size_t)257);
	if (readlink(node->path, buf, 256) == -1)
		exit_readlink_error(buf);
	lstat(buf, &filestat);
	if (S_ISDIR(filestat.st_mode) && !(opendir(buf)) && !(opts & LON))
	{
		if (opts & DIR_NAME)
			ft_printf("\n%s:\n", node->name);
		ft_putstr_fd("ft_ls: ", 2);
		perror(node->name);
	}
	else
	{
		if (opts & LON)
			print_long_list_node(node);
		else
			ft_printf("%s\n", node->name);
	}
}

void	add_symbolic_link(t_node *node)
{
	node->l_opt->sym_link = (char *)malloc(sizeof(char) * 256);
	if (!node->l_opt->sym_link)
		exit_malloc_error(node->name);
	if (readlink(node->path, node->l_opt->sym_link, 256) == -1)
		exit_readlink_error(node->l_opt->sym_link);
}

void	list_add_long(t_node *node, struct stat filestat, t_inf *info)
{
	char			*date;

	node->l_opt = (t_long *)malloc(sizeof(t_long));
	if (!node->l_opt)
		error_dir(node->name);
	list_add_long_filetype(node, filestat, 9);
	node->l_opt->size = (int)filestat.st_size;
	node->l_opt->links = (int)filestat.st_nlink;
	get_owner_group(node, filestat);
	date = ctime(&filestat.st_ctimespec.tv_sec);
	node->l_opt->year = ft_atoi((const char *)&date[20]);
	ft_strncpy(node->l_opt->date, (const char *)&date[4], (size_t)12);
	node->l_opt->date[12] = '\0';
	if (node->type == 10)
		add_symbolic_link(node);
	info->total += (long)filestat.st_blocks;
}
