/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:40:55 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/25 23:07:14 by rvuorenl         ###   ########.fr       */
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
	else
	{
		if ((options & REVERSE) && (node->type != 0))	//	errors go to front of the list, in ascii order
			list_find_spot_r(head, prev, node, tmp);
		else
			list_find_spot(head, prev, node, tmp);
	}
}

void	create_node(t_node **head, char *name, int opts)
{
	t_node		*node;
	struct stat	filestat;

	node = (t_node*)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error("create_node");
	if (lstat(name, &filestat) == -1)
		node->type = 0;
	else
		node->type = node_filetype(filestat);
	node->name = ft_strdup_exit(name);
	node->next = NULL;
	node->sec = filestat.st_mtimespec.tv_sec;
	node->n_sec = filestat.st_mtimespec.tv_nsec;
	if (opts & LONG)
		list_add_long(node, filestat);
	list_sort_add(head, node, opts);
}

			// 	version with filetype = 0 NOT WORKING
// void	create_node(t_node **head, struct stat filestat, char *name, int opts)
// {
// 	t_node	*node;

// 	node = (t_node*)malloc(sizeof(t_node));
// 	if (!node)
// 		exit_malloc_error("create_node");
// 	node->type = node_filetype(filestat);
// 	node->name = ft_strdup_exit(name);
// 	node->next = NULL;
// 	node->sec = filestat.st_mtimespec.tv_sec;
// 	node->n_sec = filestat.st_mtimespec.tv_nsec;
// 	if (opts & LONG)
// 		list_add_long(node, filestat);
// 	list_sort_add(head, node, opts);
// }
