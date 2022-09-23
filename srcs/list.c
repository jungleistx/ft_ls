/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:40:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/23 12:35:18 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	list_sort_add(t_node **head, t_node *node, int options)
{
	t_node	*tmp;
	t_node	*prev;

	tmp = *head;
	prev = NULL;
	if (!tmp)
		*head = node;
	else if (options & REVERSE && node->type != 0)
		list_find_spot_r(head, prev, node, tmp);
	else
		list_find_spot(head, prev, node, tmp);
	if (node->type != 0 && options & SORT_TIME && options & REVERSE)
		list_sort_time_reverse(head);
	else if (node->type != 0 && options & SORT_TIME)
		list_sort_time(head);
}

int	check_link_validity(t_node *node, int opts)
{
	struct stat	filestat;
	char		buf[257];

	ft_bzero((void *)buf, (size_t)257);
	if (readlink(node->path, buf, 256) == -1)
		exit_readlink_error(buf);
	lstat(buf, &filestat);
	if (S_ISDIR(filestat.st_mode) && !(opendir(buf)) && !(opts & LON))
		return (1);
	return (10);
}

int	node_filetype(struct stat filestat, t_node *node, int opts)
{
	if (S_ISDIR(filestat.st_mode))
		return (4);
	else if (S_ISREG(filestat.st_mode))
		return (8);
	else if (S_ISCHR(filestat.st_mode))
		return (2);
	else if (S_ISBLK(filestat.st_mode))
		return (3);
	else if (S_ISLNK(filestat.st_mode))
		return (check_link_validity(node, opts));
	else
		return (0);
}

char	*get_full_path(char *name, char *path)
{
	size_t	total;
	char	*full_path;

	total = ft_strlen(name) + ft_strlen(path) + 2;
	full_path = (char *)malloc(total);
	if (!full_path)
		exit_malloc_error(name);
	full_path = ft_strcpy(full_path, path);
	if (name[0] != '/' && name[0] != '~')
		full_path = ft_strcat(full_path, "/");
	full_path = ft_strcat(full_path, name);
	return (full_path);
}

void	create_node(t_node **head, char *name, t_inf *info, char *path)
{
	t_node		*node;
	struct stat	filestat;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error(name);
	node->path = get_full_path(name, path);
	if (lstat(node->path, &filestat) == -1)
	{
		node->type = 0;
		info->options |= ERROR_FILE;
	}
	else
		node->type = node_filetype(filestat, node, info->options);
	node->name = ft_strdup_exit(name);
	node->next = NULL;
	node->sec = filestat.st_mtimespec.tv_sec;
	node->n_sec = filestat.st_mtimespec.tv_nsec;
	if (info->options & LON && node->type != 0)
		list_add_long(node, filestat, info);
	list_sort_add(head, node, info->options);
}
