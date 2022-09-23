/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:42:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/23 19:09:49 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	free_error_nodes(t_node **head, int options)
{
	t_node	*tmp;
	t_node	*prev;
	t_node	*next;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			next = tmp->next;
			if (!prev)
				*head = next;
			free_node(tmp, options);
			tmp = next;
			if (prev)
				prev->next = tmp;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	get_owner_group(t_node *node, struct stat filestat)
{
	struct passwd	*user;
	struct group	*g_id;

	user = getpwuid(filestat.st_uid);
	if (!user)
		node->l_opt->owner = ft_itoa((int)filestat.st_uid);
	else
		node->l_opt->owner = ft_strdup_exit(user->pw_name);
	g_id = getgrgid(filestat.st_gid);
	if (!g_id)
		node->l_opt->group = ft_itoa((int)filestat.st_gid);
	else
		node->l_opt->group = ft_strdup_exit(g_id->gr_name);
}

void	print_year(t_node *node)
{
	time_t		cur_time;
	struct stat	filestat;

	lstat(node->path, &filestat);
	if (time(&cur_time) == -1)
	{
		perror("time");
		exit(5);
	}
	if (cur_time - filestat.st_ctimespec.tv_sec > (2629743 * 6)
		|| filestat.st_ctimespec.tv_sec - cur_time > (2629743 * 6))
	{
		write (1, node->l_opt->date, 7);
		ft_printf ("%d  ", node->l_opt->year);
	}
	else
		ft_printf("%s ", node->l_opt->date);
}

void	print_major_minor(t_node *node)
{
	unsigned int	minor;
	unsigned int	major;

	if (node->type == 2 || node->type == 3)
	{
		minor = (node->l_opt->majorminor & 0xffffff);
		major = (node->l_opt->majorminor & (0xff << 24));
		major = major >> 24;
		ft_printf("%u, %u ", major, minor);
	}
	else
		ft_printf("%-*d ", 7, node->l_opt->size);
}
