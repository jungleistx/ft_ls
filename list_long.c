/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:34:34 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/15 13:21:38 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_add_long_filetype(t_node *node, struct stat filestat, int a)
{
	ft_memset((void *)node->l_opt->permissions, '-', 10);
	if (node->type == 4)
		node->l_opt->permissions[0] = 'd';
	else if (node->type == 10)
		node->l_opt->permissions[0] = 'l';
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

char	*add_symbolic_link(t_node *node)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 256);
	if (!buf)
		exit_malloc_error("add_symbolic_link");
	if (readlink(node->path, buf, 256) == -1)
		exit_readlink_error(buf);
	return (buf);
}

void	list_add_long(t_node *node, struct stat filestat, t_info *info)
{
	struct passwd	*user;
	struct group	*g_id;
	char			*date;

	node->l_opt = (t_long *)malloc(sizeof(t_long));
	if (!node->l_opt)
		error_dir("list_add_long malloc");
	list_add_long_filetype(node, filestat, 9);
	node->l_opt->size = (int)filestat.st_size;
	node->l_opt->links = (int)filestat.st_nlink;
	user = getpwuid(filestat.st_uid);
	g_id = getgrgid(user->pw_gid);
	node->l_opt->owner = ft_strdup_exit(user->pw_name);
	node->l_opt->group = ft_strdup_exit(g_id->gr_name);
	date = ctime(&filestat.st_ctimespec.tv_sec);
	node->l_opt->year = ft_atoi((const char *)&date[20]);
	ft_strncpy(node->l_opt->date, (const char *)&date[4], (size_t)12);
	node->l_opt->date[12] = '\0';
	if (node->type == 10)
		node->l_opt->sym_link = add_symbolic_link(node);
	info->total += (long)filestat.st_blocks;
}
