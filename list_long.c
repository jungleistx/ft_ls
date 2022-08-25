/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:34:34 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/25 20:49:45 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_add_long_filetype(t_node *node, struct stat filestat, int a)
{
	if (node->type == 4)
		node->l_opt->permissions[0] = 'd';
	else if (node->type == 10)
		node->l_opt->permissions[0] = 'l';
	// else if (node->type == 8)
	// 	node->l_opt->permissions[0] = '-';
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

		// char *str = "----------"	INITIALIZE !!

}

// void	list_add_long(t_node *node, struct stat filestat)
// {
// 	struct passwd	*user;
// 	struct group	*g_id;
// 	char			*date;

// 	node->l_opt = (t_long*)malloc(sizeof(t_long));
// 	if (!node->l_opt)
// 		error_dir("list_add_long malloc");
// 	list_add_long_filetype(node, filestat, 9);
// 	node->l_opt->size = (int)filestat.st_size;
// 	node->l_opt->links = (int)filestat.st_nlink;
// 	user = getpwuid(filestat.st_uid);
// 	g_id = getgrgid(user->pw_gid);
// 	ft_strdup_exit(user->pw_name, node->l_opt->owner);
// 	ft_strdup_exit(g_id->gr_name, node->l_opt->group);
// 	date = ctime(&filestat.st_ctimespec.tv_sec);
// 	node->l_opt->year = ft_atoi((const char*)&date[20]);
// 	ft_strncpy(node->l_opt->date, (const char*)&date[4], (size_t)15);
// 	node->l_opt->date[15] = '\0';
// }
