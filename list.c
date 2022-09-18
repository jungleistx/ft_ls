/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:40:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 13:38:02 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// int	check_link_validity(t_node *node, int opts)
// {
// 	struct stat	filestat;
// 	char		buf[257];

// 	if (readlink(node->path, buf, 256) == -1)
// 		exit_readlink_error(buf);
// 	lstat(buf, &filestat);
// 	if (S_ISDIR(filestat.st_mode) && !(opendir(buf) && !(opts & LONG))
// 		return (1);
// 	return (10);
// }

int	node_filetype(struct stat filestat, t_node *node, int opts)
{
	if (S_ISDIR(filestat.st_mode))
		return (4);
	else if (S_ISREG(filestat.st_mode))
		return (8);
	else if (S_ISLNK(filestat.st_mode))
		return (check_link_validity(node, opts));
	else
		return (0);
}

void	list_find_spot_r(t_node **head, t_node *prev, t_node *node, t_node *tmp)
{
	while (tmp)
	{
		if (ft_strcmp((const char*)node->name, (const char*)tmp->name) > 0)
		{
			if (*head == tmp)
				*head = node;
			if (prev)
				prev->next = node;
			node->next = tmp;
			return ;
		}
		else
		{
			prev = tmp;
			if (tmp->next)
				tmp = tmp->next;
			else
			{
				tmp->next = node;
				return ;
			}
		}
	}
}

void	list_find_spot(t_node **head, t_node *prev, t_node *node, t_node *tmp)
{
	while (tmp)
	{
		if (ft_strcmp((const char*)node->name, (const char*)tmp->name) < 0)
		{
			if (*head == tmp)
				*head = node;
			if (prev)
				prev->next = node;
			node->next = tmp;
			return ;
		}
		else
		{
			prev = tmp;
			if (tmp->next)
				tmp = tmp->next;
			else
			{
				tmp->next = node;
				return ;
			}
		}
	}
}

void	list_sort_add(t_node **head, t_node *node, int options)
{
	t_node	*tmp;
	t_node	*prev;

	tmp = *head;
	prev = NULL;
	if (!tmp)
		*head = node;
	else if (options & REVERSE && node->type != 0)	//	errors go to front of the list
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
	// struct stat	filestat1;
	char		buf[257];

	ft_bzero((void *)buf, (size_t)257);
	if (readlink(node->path, buf, 256) == -1)
		exit_readlink_error(buf);
	lstat(buf, &filestat);
	// lstat("dirtest01/noperm", &filestat1);
	// printf("	validity --%s-- %d\n", buf, filestat.st_mode);
	if (S_ISDIR(filestat.st_mode) && !(opendir(buf)) && !(opts & LONG))
		// printf("1---");
	// if (S_ISDIR(filestat1.st_mode) && !(opendir("dirtest01/noperm")) && !(opts & LONG))
	// 	printf("2---");
		return (1);
	return (10);
}

void	create_node(t_node **head, char *name, t_info *info, char *path)
{
	t_node		*node;
	struct stat	filestat;

	node = (t_node*)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error("create_node");

	node->path = get_full_path(name, path);

	if (lstat(node->path, &filestat) == -1)
		node->type = 0;
	else
		node->type = node_filetype(filestat, node, info->options);
	node->name = ft_strdup_exit(name);
	node->next = NULL;
	node->sec = filestat.st_mtimespec.tv_sec;
	node->n_sec = filestat.st_mtimespec.tv_nsec;
	if (info->options & LONG && node->type != 0)
		list_add_long(node, filestat, info);
	list_sort_add(head, node, info->options);
}

char	*get_full_path(char *name, char *path)
{
	size_t	total;
	char	*full_path;

	total = ft_strlen(name) + ft_strlen(path) + 2;
	full_path = (char*)malloc(total);
	if (!full_path)
		exit_malloc_error("get_full_path");


	full_path = ft_strcpy(full_path, path);
	if (name[0] != '/' && name[0] != '~')
		full_path = ft_strcat(full_path, "/");
	// path = libft 5
	// mid = '/'	1
	// name = abc	3
	// 0 1 2 3 4 5 6 7 8 9
	// l i b f t / a b c \0
	full_path = ft_strcat(full_path, name);
	//printf("full '%s', name '%s, path %s\n", full_path, name, path);

	//exit(0);
	// free(path);
	// printf("IN GET PATH, path %s, name %s\n", path, name);
	// printf("in get_path: path = '%s', name = '%s'\n", path, name);
	// printf("in get_path: full = '%s'\n", full_path);
	return (full_path);
}
