/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:40:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/12 16:22:48 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	node_filetype(struct stat filestat)
{
	if (S_ISDIR(filestat.st_mode))
		return (4);
	else if (S_ISREG(filestat.st_mode))
		return (8);
	else if (S_ISLNK(filestat.st_mode))
		return (10);
	else
		return (0);
		// need to check spesific error with new func?
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

// list_find_spot(head, prev, node, tmp);
// tmp = traverse list
// node = to add

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
	else if (options & SORT_TIME && options & REVERSE && node->type != 0)
		list_sort_time_reverse(head);
	else if (options & SORT_TIME && node->type != 0)
		list_sort_time(head);
	else if (options & REVERSE && node->type != 0)	//	errors go to front of the list
		list_find_spot_r(head, prev, node, tmp);
	else
		list_find_spot(head, prev, node, tmp);

	//			V2 - longer but more readable?
	// else if (node->type != 0)
	// {
	// 	if (options & SORT_TIME && options & REVERSE)
	// 		list_sort_time_reverse(head);
	// 	else if (options & SORT_TIME)
	// 		list_sort_time(head);
	// 	else if (options & REVERSE)
	// 		list_find_spot_r(head, prev, node, tmp);
	// 	else
	// 		list_find_spot(head, prev, node, tmp);
	// }
	// else
	// 	list_find_spot(head, prev, node, tmp);

	// 		OLD VERSION AFTER IF
	// else
	// {
	// 	if ((options & REVERSE) && (node->type != 0))	//	errors go to front of the list, in ascii order
	// 		list_find_spot_r(head, prev, node, tmp);
	// 	else
	// 		list_find_spot(head, prev, node, tmp);
	// }
}

// void	create_node(t_node **head, char *name, int opts, char *path)
void	create_node(t_node **head, char *name, t_info *info, char *path)
{
	t_node		*node;
	struct stat	filestat;
	// char		*full_path;

	node = (t_node*)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error("create_node");

	// full_path = get_full_path(name, path);
	node->path = get_full_path(name, path);

	// if (lstat(full_path, &filestat) == -1)
	if (lstat(node->path, &filestat) == -1)
		node->type = 0;
	else
		node->type = node_filetype(filestat);
	// node->path = ft_strdup_exit(full_path); // remove the node->name ?
	// free(full_path);
	node->name = ft_strdup_exit(name);
	node->next = NULL;
	node->sec = filestat.st_mtimespec.tv_sec;
	node->n_sec = filestat.st_mtimespec.tv_nsec;
	if (info->options & LONG)
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
	full_path = ft_strcat(full_path, "/");
	// path = libft 5
	// mid = '/'	1
	// name = abc	3
	// 0 1 2 3 4 5 6 7 8 9
	// l i b f t / a b c \0
	full_path = ft_strcat(full_path, name);
	// free(path);

	// printf("in get_path: path = '%s', name = '%s'\n", path, name);
	// printf("in get_path: full = '%s'\n", full_path);
	return (full_path);
}

//name = filename
//full = path to filename
void	create_node_fullpath(t_node **head, char *name, t_info *i, char *path)
{
	t_node		*node;
	struct stat	filestat;
	char		*full_path;

	node = (t_node*)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error("create_node");

//
	// printf("\nin create_node: path = '%s', name = '%s'\n", path, name);
	full_path = get_full_path(name, path);
	// printf("in create_node after: full_path = '%s'\n", full_path);
	if (lstat(full_path, &filestat) == -1)
		node->type = 0;
	else
		node->type = node_filetype(filestat);
	free(full_path);
//

	node->name = ft_strdup_exit(name);
	node->next = NULL;
	node->sec = filestat.st_mtimespec.tv_sec;
	node->n_sec = filestat.st_mtimespec.tv_nsec;
	if (i->options & LONG)
		list_add_long(node, filestat, i);
	list_sort_add(head, node, i->options);
}
